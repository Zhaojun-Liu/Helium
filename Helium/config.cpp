/*
* Helium Pre-Alpha 0.6.1
* Copyright (C) 2021-2022 HeliumDevTeam
*
* Helium is a customizable extension system for Minecraft server which is written in C++.
* This project is inspired by the [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged).
* We target to provide a liter, faster, and more customizable choice.
* As a trade-off, we sacrifice its portability and the simplicity of writing extensions.
* (we r sry that we haven't finish the first alpha version yet, if u r interested in our project, we recommend u to use mcdr as a temporary alternative)
* This project is licensed by the GPL-3.0-or-later license.
*
* Very very special thank to contributors of the following projects:
* [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged)
* [kpeeters/tree.hh](https://github.com/kpeeters/tree.hh)
* [leethomason/tinyxml2](https://github.com/leethomason/tinyxml2/)
* [jcwangxp/Crossline](https://github.com/jcwangxp/Crossline/)
*
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
*
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*    This file is part of Helium.
*
*    Helium is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Helium is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#include"config.h"
namespace Helium {
    vector<HeliumAttribute> attrlist;
    HeliumLogger cfglogger("HeliumConfigReader");

    START_CONFIG_NODES_REGISTER;

    int ConfigNode::Print() {
        HeliumEndline hendl;
        cfglogger << HLL::LL_DBG <<"NodeName:" << this->nodename << hendl;
        cfglogger << "ValueType:" << this->valuetype << hendl;
        switch (this->valuetype)
        {
        [[likely]] case VALUE_TYPE_INTEGER:
            try {
                auto value = std::get<int>(this->var); // access by type
                cfglogger << "Value:" << value << hendl;
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cfglogger << "Failed to get the value" << hendl;
            }
            break;
        [[likely]] case VALUE_TYPE_DOUBLE:
            try {
                auto value = std::get<double>(this->var); // access by type
                cfglogger << "Value:" << value << hendl;
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cfglogger << "Failed to get the value" << hendl;
            }
            break;
        [[likely]] case VALUE_TYPE_STRING:
            try {
                auto value = std::get<string>(this->var); // access by type
                cfglogger << "Value:" << value << hendl;
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cfglogger << "Failed to get the value" << hendl;
            }
            break;
        [[likely]] case VALUE_TYPE_BOOLEAN:
            try {
                auto temp = std::get<bool>(this->var); // access by type
                auto value = boolstr[temp];
                cfglogger << "Value:" << value << hendl;
            }
            catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                cfglogger << "Failed to get the value" << hendl;
            }
            break;
        [[unlikely]] default:
            break;
        }
        cout << endl;
        return 0;
    }


    [[nodiscard("Do not discard return value of SaveConfigFile() plz")]]
    int _stdcall SaveConfigFile() {
        HeliumEndline hendl;
        cfglogger << HLL::LL_INFO << "Saving config file..." << hendl;
        tinyxml2::XMLDocument doc;
        if (auto ret = doc.LoadFile(CFG_FILENAME); ret != 0) {
            cfglogger << HLL::LL_CRIT << "Failed to create XML file declaration for config file" << hendl;
            return -1;
        }

        tinyxml2::XMLElement* root = doc.NewElement("HeliumConfig");
        doc.InsertEndChild(root);

        for (auto node : _confignodes_) {
            stringstream sstr;

            switch (node.valuetype)
            {
            [[likely]] case VALUE_TYPE_INTEGER:
                try {
                    sstr << std::get<int>(node.var); // access by type
                    tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                    tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                    root->InsertEndChild(newelement);
                    newelement->InsertEndChild(newtext);
                }
                catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                    cfglogger << HLL::LL_CRIT << "Failed to get the value of : " << node.nodename << hendl;
                }
                break;
            [[likely]] case VALUE_TYPE_DOUBLE:
                try {
                    sstr << std::get<double>(node.var); // access by type
                    tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                    tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                    root->InsertEndChild(newelement);
                    newelement->InsertEndChild(newtext);
                }
                catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                    cfglogger << HLL::LL_CRIT << "Failed to get the value of : " << node.nodename << hendl;
                }
                break;
            [[likely]] case VALUE_TYPE_STRING:
                try {
                    sstr << std::get<string>(node.var); // access by type
                    tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                    tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                    root->InsertEndChild(newelement);
                    newelement->InsertEndChild(newtext);
                }
                catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                    cfglogger << HLL::LL_CRIT << "Failed to get the value of : " << node.nodename << hendl;
                }
                break;
            [[likely]] case VALUE_TYPE_BOOLEAN:
                try {
                    sstr << boolstr[std::get<bool>(node.var)]; // access by type
                    tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                    tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                    root->InsertEndChild(newelement);
                    newelement->InsertEndChild(newtext);
                }
                catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                    cfglogger << HLL::LL_CRIT << "Failed to get the value of : " << node.nodename << hendl;
                }
                break;
            [[unlikely]] default:
                break;
            }

            sstr.clear();
        }

        if (auto ret = doc.SaveFile(CFG_FILENAME); ret != 0) {
            cfglogger << HLL::LL_WARN << "Failed to save the main config file" << hendl;
            return -1;
        }

        cfglogger << HLL::LL_INFO << "Done." << hendl;

        return 0;
    }

    [[nodiscard("Ignoring return value may cause config file create incorrectly.")]]
    int _stdcall CreateConfigFile()
    {
        const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
        HeliumEndline hendl;
        cfglogger << HLL::LL_INFO << "Creating config file..." << hendl;
        tinyxml2::XMLDocument doc;

        if (auto ret = doc.Parse(declaration); ret != 0) {
            cfglogger << HLL::LL_CRIT << "Failed to create XML file declaration for config file" << hendl;
            return -1;
        }

        tinyxml2::XMLElement* root = doc.NewElement("HeliumConfig");
        doc.InsertEndChild(root);

        for (auto node : _confignodes_) {
            stringstream sstr;

            switch (node.valuetype)
            {
            [[likely]] case VALUE_TYPE_INTEGER:
                try {
                    sstr << std::get<int>(node.var); // access by type
                    tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                    tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                    root->InsertEndChild(newelement);
                    newelement->InsertEndChild(newtext);
                }
                catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                    cfglogger << HLL::LL_CRIT << "Failed to get the value of : " << node.nodename << hendl;
                }
                break;
            [[likely]] case VALUE_TYPE_DOUBLE:
                try {
                    sstr << std::get<double>(node.var); // access by type
                    tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                    tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                    root->InsertEndChild(newelement);
                    newelement->InsertEndChild(newtext);
                }
                catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                    cfglogger << HLL::LL_CRIT << "Failed to get the value of : " << node.nodename << hendl;
                }
                break;
            [[likely]] case VALUE_TYPE_STRING:
                try {
                    sstr << std::get<string>(node.var); // access by type
                    tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                    tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                    root->InsertEndChild(newelement);
                    newelement->InsertEndChild(newtext);
                }
                catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                    cfglogger << HLL::LL_CRIT << "Failed to get the value of : " << node.nodename << hendl;
                }
                break;
            [[likely]] case VALUE_TYPE_BOOLEAN:
                try {
                    sstr << boolstr[std::get<bool>(node.var)]; // access by type
                    tinyxml2::XMLElement* newelement = doc.NewElement(node.nodename.c_str());
                    tinyxml2::XMLText* newtext = doc.NewText(sstr.str().c_str());
                    root->InsertEndChild(newelement);
                    newelement->InsertEndChild(newtext);
                }
                catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
                    cfglogger << HLL::LL_CRIT << "Failed to get the value of : " << node.nodename << hendl;
                }
                break;
            [[unlikely]] default:
                break;
            }

            sstr.clear();
        }

        if (auto ret = doc.SaveFile(CFG_FILENAME); ret != 0) {
            cfglogger << HLL::LL_WARN << "Failed to save config file" << hendl;
            return -1;
        }

        cfglogger << HLL::LL_INFO << "Done." << hendl;

        return 0;
    }

    [[nodiscard("Ignoring return value may cause invaild attribute value.")]]
    int _stdcall ReadConfigFile() {
        tinyxml2::XMLDocument config;
        tinyxml2::XMLElement* pRootEle;
        HeliumEndline hendl;
        stringstream sstr;
        string str;

        cfglogger << HLL::LL_INFO << "Reading config file..." << hendl;

        auto ret = config.LoadFile(CFG_FILENAME);

        if (ret != tinyxml2::XMLError::XML_SUCCESS) {
            int iret = CreateConfigFile();
            return ReadConfigFile();
        }

        if (pRootEle = config.RootElement(); pRootEle == NULL) {
            return -1;
        }

        for (auto node = _confignodes_.begin(); node < _confignodes_.end(); node++)
        {
            if (node->valuetype != VALUE_TYPE_BOOLEAN) {
                string temp = gnsbn(node->nodename);
                istringstream iss(temp);
                switch (node->valuetype)
                {
                case VALUE_TYPE_INTEGER:
                    int itemp;
                    iss >> itemp;
                    node->var.emplace<VALUE_TYPE_INTEGER>(itemp);
                    break;
                case VALUE_TYPE_DOUBLE:
                    double dtemp;
                    iss >> dtemp;
                    node->var.emplace<VALUE_TYPE_DOUBLE>(dtemp);
                    break;
                case VALUE_TYPE_STRING:
                    node->var.emplace<VALUE_TYPE_STRING>(temp);
                    break;
                default:
                    break;
                }
            }
            else if (node->valuetype == VALUE_TYPE_BOOLEAN) {
                string temp = gnsbn(node->nodename);
                bool tempbool;
                istringstream(temp) >> boolalpha >> tempbool;
                if (temp == "True") {
                    node->var.emplace<VALUE_TYPE_BOOLEAN>(tempbool);
                }
                else {
                    node->var.emplace<VALUE_TYPE_BOOLEAN>(tempbool);
                }
            }
        }

        cfglogger << HLL::LL_INFO << "Done." << hendl;
        return 0;
    }

    int _stdcall Config() {
        HeliumEndline hendl;

        ADD_CONFIG_NODE("EnableTimeStamp", EnableTimeStamp, VALUE_TYPE_BOOLEAN, true);
        ADD_CONFIG_NODE("Language", Language, VALUE_TYPE_INTEGER, 0);
        ADD_CONFIG_NODE("PluginDirectory", PluginDirectory, VALUE_TYPE_STRING, "plugins");
        ADD_CONFIG_NODE("MaxQueue", MaxQueue, VALUE_TYPE_INTEGER, 2048);

        if (auto ret = ReadConfigFile(); ret == -1) {
            cfglogger << HLL::LL_CRIT << "Failed to read the config file" << hendl;
            return -1;
        }
        return 0;
    }
}