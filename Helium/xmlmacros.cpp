#include"xmlmacros.h"

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