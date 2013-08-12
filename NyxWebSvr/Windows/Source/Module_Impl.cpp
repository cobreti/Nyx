#include "Module_Impl.hpp"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>



struct CRYPTO_dynlock_value
{
    HANDLE mutex;
};

static HANDLE *mutex_buf = NULL;

/**
 * OpenSSL locking function.
 *
 * @param    mode    lock mode
 * @param    n        lock number
 * @param    file    source file name
 * @param    line    source file line number
 * @return    none
 */
static void locking_function(int mode, int n, const char *file, int line)
{
    if (mode & CRYPTO_LOCK) {
        WaitForSingleObject(mutex_buf[n], INFINITE);
    } else {
        ReleaseMutex(mutex_buf[n]);
    }
}

/**
 * OpenSSL uniq id function.
 *
 * @return    thread id
 */
static unsigned long id_function(void)
{
    return ((unsigned long) ::GetCurrentThreadId() );
}

/**
 * OpenSSL allocate and initialize dynamic crypto lock.
 *
 * @param    file    source file name
 * @param    line    source file line number
 */
static struct CRYPTO_dynlock_value *dyn_create_function(const char *file, int line)
{
    struct CRYPTO_dynlock_value *value;
    
    value = (struct CRYPTO_dynlock_value *)
    malloc(sizeof(struct CRYPTO_dynlock_value));
    if (!value) {
        goto err;
    }
	value->mutex = ::CreateMutex(NULL, FALSE, NULL);
    
    return value;
    
err:
    return (NULL);
}

/**
 * OpenSSL dynamic locking function.
 *
 * @param    mode    lock mode
 * @param    l        lock structure pointer
 * @param    file    source file name
 * @param    line    source file line number
 * @return    none
 */
static void dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l,
                              const char *file, int line)
{
    if (mode & CRYPTO_LOCK) {
        WaitForSingleObject(l->mutex, INFINITE);
    } else {
        ReleaseMutex(l->mutex);
    }
}

/**
 * OpenSSL destroy dynamic crypto lock.
 *
 * @param    l        lock structure pointer
 * @param    file    source file name
 * @param    line    source file line number
 * @return    none
 */

static void dyn_destroy_function(struct CRYPTO_dynlock_value *l,
                                 const char *file, int line)
{
    CloseHandle(l->mutex);
    free(l);
}

/**
 * Initialize TLS library.
 *
 * @return    0 on success, -1 on error
 */
int tls_init(void)
{
    int i;
    
    /* static locks area */
    mutex_buf = (HANDLE *) malloc(CRYPTO_num_locks() * sizeof(HANDLE));
    if (mutex_buf == NULL) {
        return (-1);
    }
    for (i = 0; i < CRYPTO_num_locks(); i++) {
        mutex_buf[i] = CreateMutex(NULL, FALSE, NULL);
    }
    /* static locks callbacks */
    CRYPTO_set_locking_callback(locking_function);
    CRYPTO_set_id_callback(id_function);
    /* dynamic locks callbacks */
    CRYPTO_set_dynlock_create_callback(dyn_create_function);
    CRYPTO_set_dynlock_lock_callback(dyn_lock_function);
    CRYPTO_set_dynlock_destroy_callback(dyn_destroy_function);
    
    SSL_load_error_strings();
    SSLeay_add_ssl_algorithms();
    
    //    RAND_load_file("/dev/urandom", 1024);
    
    return (0);
}




NyxWebSvr::CModuleRef NyxWebSvr::CModule::Alloc()
{
    return new NyxWebSvr::CModule_Impl();
}


namespace NyxWebSvr
{
    
    /**
     *
     */
    CModule_Impl::CModule_Impl()
    {
        CRYPTO_malloc_init(); // Initialize malloc, free, etc for OpenSSL's use
        SSL_library_init(); // Initialize OpenSSL's SSL libraries
        SSL_load_error_strings(); // Load SSL error strings
        ERR_load_BIO_strings(); // Load BIO error strings
        OpenSSL_add_all_algorithms(); // Load all available encryption algorithms
        tls_init();
    }
    
    
    /**
     *
     */
    CModule_Impl::~CModule_Impl()
    {
        
    }
    
}
