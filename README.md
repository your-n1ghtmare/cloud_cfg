# cloud_cfg

**the project was created to show how to quickly send the json cfg to the server and get it back**

# thirdparty

- [json](https://github.com/nlohmann/json/)
- [HTTPRequest](https://github.com/elnormous/HTTPRequest/)

# example

- create cfg var's

**sdk::cfg_var_t< bool > a{ "apple", false };**    
**sdk::cfg_var_t< float > b{ "banana", 1 };**    
**sdk::cfg_var_t< int > c{ "orange", 10 };**    

- func to upload json file to server

**g_cfg->upload_cfg("your.n1ghtmare");**

- func to get json file from server

**g_cfg->get_cfg("your.n1ghtmare");**
