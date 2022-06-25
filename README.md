# EasyGen
### Whats is it?
Code generation tool for data transfer models (DTO) using IDL (very simple  yaml conf)

## Goal
automatization routine procedures by code filling getters, setters and make correct syntax, for example: serialization/deserialization

### Used
* For generations - uses mustache generator.
* C++ 14
* Boost (dll, filesystem, program_options)
* mustache lib
* yaml-cpp
* cmake


### How to use?
#### Example Syntax Yaml Config for data models (User and RegistredUser)
```yaml
models:
  User:
    type: "object"
    properties:
      id:
        type: "int64"
      username:
        type: "string"
      firstName:
        type: "string"
      lastName:
        type: "string"
      email:
        type: "string"
      password:
        type: "string"
      phone:
        type: "bool"
      userStatus:
        type: "int32"
        description: "User Status"
  RegistredUser:
    type: "object"
    properties: 
      id:
        type: "uint64"
        description: "User ID"
      phone:
        type: "string"
```

#### Result (For msgpack generator User.hpp)
<details>
  <summary>Click to view</summary>
  
```cpp
#pragma  once

#ifndef User_H_

#define User_H_

  

#include  <string>

#include  "IBinarySerializer.hpp"

#include  <msgpack.hpp>

  

namespace  io {

namespace  codegen {

namespace  datamodel {

  

class  User : public  io::codegen::datamodel::IBinarySerializer {

  

public:

User();

~User() override = default;

  

int64_t  get_id() const;

void  set_id(int64_t  id_in);

std::string  get_username() const;

void  set_username(std::string  username_in);

std::string  get_firstName() const;

void  set_firstName(std::string  firstName_in);

std::string  get_lastName() const;

void  set_lastName(std::string  lastName_in);

std::string  get_email() const;

void  set_email(std::string  email_in);

std::string  get_password() const;

void  set_password(std::string  password_in);

bool  get_phone() const;

void  set_phone(bool  phone_in);

int32_t  get_userStatus() const;

void  set_userStatus(int32_t  userStatus_in);

  

/*!

* @brief Serialization object to binary format

* @return byte array

*/

std::vector<uint8_t> ToBinary() const  override;

/*!

* @brief Deserialization from binary format

* @param  data_in byte array (serialized object)

* @return successful/unsuccessful operation

*/

bool  FromBinary(const  std::vector<uint8_t>&  data_in) override;

  
  

MSGPACK_DEFINE(m_id, m_username, m_firstName, m_lastName, m_email, m_password, m_phone, m_userStatus);

  

protected:

int64_t m_id;

std::string m_username;

std::string m_firstName;

std::string m_lastName;

std::string m_email;

std::string m_password;

bool m_phone;

int32_t m_userStatus;

public:

friend  bool  operator==(const  User&  lhs, const  User&  rhs)

{

return  std::tie(lhs.m_id, lhs.m_username, lhs.m_firstName, lhs.m_lastName, lhs.m_email, lhs.m_password, lhs.m_phone, lhs.m_userStatus) == std::tie(rhs.m_id, rhs.m_username, rhs.m_firstName, rhs.m_lastName, rhs.m_email, rhs.m_password, rhs.m_phone, rhs.m_userStatus);

}

  

friend bool operator!=(const User& lhs, const User& rhs)

{

return !(lhs == rhs);

}

};

  

} // datamodel

} // codegen

} // io

  

#endif /* User_H_ */
```
</details>

### Syntax

* Yaml
* Main list at yaml -> models

|field| description  |
|--|--|
| 'models' | main section - contains all models for generation at this config |
| element list of models| name of concrete data model |
| element type| now only object |
| 'properties'| list properties for concrete data model |
| element list of properties| name of concrete property|
| 'type' for element list of properties| type for concrete property (supported types below) |


### Supported types (Default, but you can make any)
|yaml type| eq (example for cpp) |default value (example for cpp) |
|--|--|--|
|string  | std::string | "" |
|int32| int32_t | 0 |
|int64| int64_t | 0 |
|uint32| uint32_t | 0 |
|uint32| uint32_t | 0 |
|bool| bool | false |
|byte| uint8_t | 0x00 |


### How to build tool from sources
 Easy way - using vcpkg at manifest mode.
 docs : https://vcpkg.readthedocs.io/en/latest/users/manifests/
#### Example:
just set variable for CMAKE_TOOLCHAIN_FILE := path to vcpkg.cmake
and set VCPKG_TARGET_TRIPLET = x64-windows-static-md (example)
and wait :)

### Supported generators
 - Msgpack Serialization for C++ (and getters and setters for properties)


