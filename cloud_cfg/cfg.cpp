#include "sdk.hpp"

namespace sdk {

    void c_cfg::upload_cfg(const std::string user_name) {
  
        nlohmann::json json{};

        auto& object = json[ "cfg" ];

        for ( const auto& var : m_vars )
            var->save( object );

        auto str = json.dump( );
      
        try
        { 
            http::Request request("http://01.01.01.101/json.php?username=" + user_name + "&upload");
            request.send("POST", str, {{"Content-Type", "application/json"} });
        }
        catch (const std::exception& e)
        {
            MessageBoxA(0, "request failed, error: ", e.what(), MB_OK);
            return;
        }

    }

    void c_cfg::get_cfg(const std::string user_name) {
     
        std::string str{};

        try 
        {    
            http::Request request{ "http://01.01.01.101/json.php?username=" + user_name + "&get" };

            const auto response = request.send("GET");
            str = std::string{ response.body.begin(), response.body.end() };
        }
        catch (const std::exception& e)
        {
            MessageBoxA(0, "request failed, error: ", e.what(), MB_OK);
            return;
        }

        if ( str.empty( ) )
            return;

        const auto json = nlohmann::json::parse( str );
        if ( !json.is_object( ) )
            return;


        const auto object = json.find( "cfg" );
        if ( object == json.end( ) )
            return;

        const auto& value = object.value( );

        for ( auto& var : m_vars )
            var->load( value );
    }
}