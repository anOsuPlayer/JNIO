#ifndef JNIO_EXCEPTION
    #define JNIO_EXCEPTION

    #include <exception>

    namespace jnio {

        class jnio_exception : std::exception {
            private:
                const char* message;

            public:
                jnio_exception() = delete;
                
                jnio_exception(const char* message);

                virtual const char* what() const noexcept override;
        };
    }

#endif