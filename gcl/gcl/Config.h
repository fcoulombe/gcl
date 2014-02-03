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
#include "gcl/Assert.h"
#include "gcl/File.h"

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
	bool HasInt(const std::string &key) const { return mIntConfig.find(key) != mIntConfig.end(); }
    int GetInt(const std::string &key) 
    {
        GCLAssertMsg(mIntConfig.find(key) != mIntConfig.end(), key.c_str());
        return mIntConfig[key];
    }
	bool HasString(const std::string &key) const { return mStringConfig.find(key) != mStringConfig.end(); }
    const std::string &GetString(const std::string &key) 
    {
        GCLAssertMsg(mStringConfig.find(key) != mStringConfig.end(), key.c_str());
        return mStringConfig[key];
    }
  private:
      Config()
      {
          
          if (GCLFile::Exists(CONFIG_PATH"Default.txt"))
         {
             Parse(CONFIG_PATH"Default.txt");
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
          std::fstream fp(configFile, std::ios_base::in);
          GCLAssert(fp.good());
          const size_t BUFFER_SIZE = 1024;
          char buffer[BUFFER_SIZE];
          while (fp.good() && !fp.eof())
          {
              fp.getline(buffer, BUFFER_SIZE);
			  std::string line(buffer);
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
          }
          fp.close();
      }
      std::map<std::string, int> mIntConfig;
      std::map<std::string, std::string> mStringConfig;
  };
}
