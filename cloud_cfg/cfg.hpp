#pragma once

namespace sdk {

    struct base_cfg_var_t {
    protected:
        std::string m_str{};
    public:
        ALWAYS_INLINE constexpr base_cfg_var_t() = default;

        ALWAYS_INLINE constexpr base_cfg_var_t(const std::string str)
            : m_str{ str } {}

        virtual void save(nlohmann::json& object) const = 0;

        virtual void load(const nlohmann::json& object) = 0;

        ALWAYS_INLINE std::string str() const { return m_str; }
    };

    template < typename _value_t >
    struct cfg_var_t final : public base_cfg_var_t {
    private:
        _value_t m_value{};
    public:
        ALWAYS_INLINE constexpr cfg_var_t( ) = default;

        ALWAYS_INLINE cfg_var_t( const std::string str, const _value_t value );

        ALWAYS_INLINE _value_t* operator &( );

        ALWAYS_INLINE operator _value_t( ) const;

        ALWAYS_INLINE _value_t& get( );

        ALWAYS_INLINE void set(_value_t value);

        ALWAYS_INLINE const _value_t& get( ) const;

        void save( nlohmann::json& object ) const override;

        void load( const nlohmann::json& object ) override;
    };

    class c_cfg {
    private:
        
        std::vector< base_cfg_var_t* > m_vars{};
    public:
        void upload_cfg( const std::string user_name);

        void get_cfg(const std::string user_name );

        ALWAYS_INLINE void add_var( base_cfg_var_t* const var );

        ALWAYS_INLINE base_cfg_var_t* find_var( const std::string str ) const;
    };

    inline const auto g_cfg = std::make_unique< c_cfg >( );
}
