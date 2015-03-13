/*
 * Copyright (C) 2013 by Francois Coulombe
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <map>
#include <string>
#include <cstdlib>
#include <vector>
#include "gcl/Assert.h"
#include "gcl/File.h"
#include "gcl/StringUtil.h"

#ifdef OS_ANDROID
#	define CONFIG_FILE_NAME "AndroidConf.txt"
#else
#	define CONFIG_FILE_NAME "Default.txt"
#endif
namespace GCL
{
  class Config
  {
  public:
    static  Config &Instance()
    {
        static Config conf;
        return conf;
    }
	bool HasBool(const std::string &key) const { return mBoolConfig.find(key) != mBoolConfig.end(); }
    bool GetBool(const std::string &key) const
    {
        GCLAssertMsg(HasBool(key), key.c_str());
        return mBoolConfig.at(key);
    }
	bool HasInt(const std::string &key) const { return mIntConfig.find(key) != mIntConfig.end(); }
	int GetInt(const std::string &key) const
    {
        GCLAssertMsg(HasInt(key), key.c_str());
        return mIntConfig.at(key);
    }
	bool HasString(const std::string &key) const { return mStringConfig.find(key) != mStringConfig.end(); }
	const std::string &GetString(const std::string &key) const
    {
        GCLAssertMsg(HasString(key), key.c_str());
        return mStringConfig.at(key);
    }
  private:
      Config()
      {
          
          if (ResourceFile::Exists(CONFIG_PATH CONFIG_FILE_NAME))
         {
             Parse(CONFIG_PATH CONFIG_FILE_NAME);
         }
          else
          {
              GCLAssert(false && "We need a config file");
          }
      }

      void Parse(const char *configFile)
      {
          const std::string kIntType("int");
          const std::string kStringType("string");
          const std::string kBoolType("bool");
          ResourceFile fp(configFile);
          auto buffer = fp.ReadAll();
          std::string fileContent((const char *)std::get<0>(buffer).get(), std::get<1>(buffer));
          std::vector<std::string> lines;
          StringUtil::Explode(fileContent, lines, '\n');
#ifdef OS_WIN32
          for (std::string &line : lines)
          {
              StringUtil::TrimEnd(line);
          }
#endif
          for (std::string line : lines)
          {
        	  size_t firstSpace = line.find(' ');
        	  std::string sdataType = line.substr(0, firstSpace);

        	  size_t secondSpace = line.find(' ', firstSpace+1);
        	  std::string skey = line.substr(firstSpace+1, secondSpace-(firstSpace+1));
        	  std::string sval = line.substr( secondSpace+1, line.length()-secondSpace);
              if (sdataType == kIntType)
              {
                  mIntConfig[skey] = atoi(sval.c_str());
              }
              else if (sdataType == kStringType)
			  {
				  mStringConfig[skey]  = sval;
			  }
              else if (sdataType == kBoolType)
			  {
				  mBoolConfig[skey]  = (sval == std::string("1")) ? true : false;
				  GCLAssert(sval == std::string("1") || sval == std::string("0"));
			  }
          }
      }
      std::map<std::string, bool> mBoolConfig;
      std::map<std::string, int> mIntConfig;
      std::map<std::string, std::string> mStringConfig;
  };
}
