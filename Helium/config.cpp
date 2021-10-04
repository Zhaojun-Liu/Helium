#include"config.h"

vector<HeliumAttribute> attrlist;

START_CONFIG_NODES_REGISTER;

int ConfigNode::Print() {
    cout << "NodeName:" << this->nodename << endl;
    cout << "ValueType:" << this->valuetype << endl;
    switch (this->valuetype)
    {
    [[likely]] case VALUE_TYPE_INTEGER:
        try {
            auto value = std::get<int>(this->var); // access by type
            cout << "Value:" << value << endl;
        }
        catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
            cout << "Failed to get the value" << endl;
        }
        break;
    [[likely]] case VALUE_TYPE_DOUBLE:
        try {
            auto value = std::get<double>(this->var); // access by type
            cout << "Value:" << value << endl;
        }
        catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
            cout << "Failed to get the value" << endl;
        }
        break;
    [[likely]] case VALUE_TYPE_STRING:
        try {
            auto value = std::get<string>(this->var); // access by type
            cout << "Value:" << value << endl;
        }
        catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
            cout << "Failed to get the value" << endl;
        }
        break;
    [[likely]] case VALUE_TYPE_BOOLEAN:
        try {
            auto temp = std::get<bool>(this->var); // access by type
            auto value = boolstr[temp];
            cout << "Value:" << value << endl;
        }
        catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
            cout << "Failed to get the value" << endl;
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
    tinyxml2::XMLDocument doc;
    if (auto ret = doc.LoadFile(CFG_FILENAME); ret != 0) {
        cout << "Failed to create XML file declaration" << endl;
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
                cout << "Failed to get the value" << endl;
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
                cout << "Failed to get the value" << endl;
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
                cout << "Failed to get the value" << endl;
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
                cout << "Failed to get the value" << endl;
            }
            break;
        [[unlikely]] default:
            break;
        }

        sstr.clear();
    }

    if (auto ret = doc.SaveFile(CFG_FILENAME); ret != 0) {
        cout << "Failed to save config file" << endl;
        return -1;
    }

    return 0;
}

[[nodiscard("Ignoring return value may cause config file create incorrectly.")]]
int _stdcall CreateConfigFile()
{
    cout << "Enter CreateConfigFile()" << endl;
    const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    tinyxml2::XMLDocument doc;
    if (auto ret = doc.Parse(declaration); ret != 0) {
        cout << "Failed to create XML file declaration" << endl;
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
                cout << "Failed to get the value" << endl;
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
                cout << "Failed to get the value" << endl;
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
                cout << "Failed to get the value" << endl;
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
                cout << "Failed to get the value" << endl;
            }
            break;
        [[unlikely]] default:
            break;
        }

        sstr.clear();
    }

    if (auto ret = doc.SaveFile(CFG_FILENAME); ret != 0) {
        cout << "Failed to save config file" << endl;
        return -1;
    }

    return 0;
}

[[nodiscard("Ignoring return value may cause invaild attribute value.")]]
int _stdcall ReadConfigFile() {
    spdlog::debug("Reading config file...");

    tinyxml2::XMLDocument config;
    tinyxml2::XMLElement* pRootEle;
    
    stringstream sstr;
    string str;

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

    cout << "Done." << endl;
    return 0;
}

int _stdcall Config() {
    ADD_CONFIG_NODE("EnableTimeStamp", EnableTimeStamp, VALUE_TYPE_BOOLEAN, true);
    ADD_CONFIG_NODE("Language", Language, VALUE_TYPE_INTEGER, 0);
    ADD_CONFIG_NODE("PluginDirectory", PluginDirectory, VALUE_TYPE_STRING, "plugins");
    ADD_CONFIG_NODE("MaxQueue", MaxQueue, VALUE_TYPE_INTEGER, 2048);

    if (auto ret = ReadConfigFile(); ret == -1) {
        cout << "Failed to read the config file" << endl;
        return -1;
    }
    return 0;
}