#include "NyxNetSSLTcpIpSocket_Impl.hpp"

/**
 *
 */
NyxNet::CSSLTcpIpSocketRef NyxNet::CSSLTcpIpSocket::Alloc()
{
	return new NyxNetOSX::CSSLTcpIpSocket_Impl();
}


/**
 *
 */
NyxNetOSX::CSSLTcpIpSocket_Impl::CSSLTcpIpSocket_Impl() :
m_ctx(NULL),
m_ssl(NULL),
m_bio(NULL),
m_bSSLOwner(false)
{
    m_refSocket = NyxNet::CTcpIpSocket::Alloc();   
//    InitSSL();
}


/**
 *
 */
NyxNetOSX::CSSLTcpIpSocket_Impl::CSSLTcpIpSocket_Impl( NyxNet::CTcpIpSocketRef refSocket ) :
m_refSocket(refSocket),
m_ctx(NULL),
m_ssl(NULL),
m_bio(NULL),
m_bSSLOwner(false)
{
//    InitSSL();
}


/**
 *
 */
NyxNetOSX::CSSLTcpIpSocket_Impl::~CSSLTcpIpSocket_Impl()
{
    if ( m_bSSLOwner )
    {
//        BIO_free(m_bio);
        SSL_free(m_ssl);
        SSL_CTX_free(m_ctx);
    }
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CSSLTcpIpSocket_Impl::Listen( const Nyx::UInt32& MaxPendingConnections )
{
    return m_refSocket->Listen(MaxPendingConnections);
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CSSLTcpIpSocket_Impl::Bind( const NyxNet::TcpIpPort& Port )
{
    return m_refSocket->Bind(Port);
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CSSLTcpIpSocket_Impl::Accept( NyxNet::CTcpIpSocketRef& NewSocket )
{
    NyxNet::CTcpIpSocketRef     socket;
    Nyx::NyxResult              res;
    int                         err;
    
    res = m_refSocket->Accept(socket);
    if ( Nyx::Succeeded(res) )
    {
//        int socketid = socket->TcpIpSocketId();
//        BIO* sslclient = BIO_new_socket(socketid, BIO_NOCLOSE);
//        BIO_set_nbio(sslclient, 0);
//        SSL_set_bio(m_ssl, sslclient, sslclient);
//        
//        int r = SSL_accept(m_ssl);
//        
//        if ( r != 1 )
//        {
//            err = SSL_get_error(m_ssl, r);
//            NYXTRACE(0x0, L"SSL_accept failure (" << Nyx::CTF_Int(err) << L")" );
//            return Nyx::kNyxRes_Failure;
//        }
//        
//        if ( SSL_get_verify_result(m_ssl) != X509_V_OK)
//        {
//            NYXTRACE(0x0, L"ssl verify result failure");
//        }

        NyxNetOSX::CSSLTcpIpSocket_Impl*    pSSLSocket = new NyxNetOSX::CSSLTcpIpSocket_Impl(socket);
        pSSLSocket->SetPrivKeyFile(m_privKeyFile);
        pSSLSocket->SetPublicKeyFile(m_publicKeyFile);
        pSSLSocket->SetDhKeyFile(m_dhKeyFile);
        pSSLSocket->InitSSL();
//        pSSLSocket->m_ssl = m_ssl;
//        pSSLSocket->m_bio = m_bio;
        
        NewSocket = pSSLSocket;
        return Nyx::kNyxRes_Success;
    }
    else
    {
        NYXTRACE(0x0, L"Accept socket method failure");
    }
    
    return res;
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CSSLTcpIpSocket_Impl::Connect()
{
    return m_refSocket->Connect();
}


/**
 *
 */
void NyxNetOSX::CSSLTcpIpSocket_Impl::Disconnect()
{
    m_refSocket->Disconnect();
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CSSLTcpIpSocket_Impl::Write(	const void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& WrittenSize )
{
    WrittenSize = 0;
    
    int size = SSL_write(m_ssl, pBuffer, DataSize);
    if ( size <= 0 )
        return Nyx::kNyxRes_Failure;
    
    WrittenSize = size;
    return Nyx::kNyxRes_Success;
}


Nyx::NyxResult NyxNetOSX::CSSLTcpIpSocket_Impl::Read( void* pBuffer, const Nyx::NyxSize& DataSize, Nyx::NyxSize& ReadSize )
{
    ReadSize = 0;
    
    int size = SSL_read(m_ssl, pBuffer, DataSize);
    if ( size <= 0 )
        return Nyx::kNyxRes_Failure;
    
    ReadSize = size;    
    return Nyx::kNyxRes_Success;
}
	

/**
 *
 */
Nyx::NyxResult NyxNetOSX::CSSLTcpIpSocket_Impl::Create( const char* szIp, const NyxNet::TcpIpPort& Port )
{
    return Nyx::kNyxRes_Failure;
}


/**
 *
 */
void NyxNetOSX::CSSLTcpIpSocket_Impl::SetListener( NyxNet::ISocketListener* pListener )
{
    m_refSocket->SetListener(pListener);
}


/**
 *
 */
bool NyxNetOSX::CSSLTcpIpSocket_Impl::Valid() const
{
    return m_refSocket->Valid();
}


/**
 *
 */
Nyx::NyxResult NyxNetOSX::CSSLTcpIpSocket_Impl::Renew()
{
    return m_refSocket->Renew();
}


/**
 *
 */
void NyxNetOSX::CSSLTcpIpSocket_Impl::SetPrivKeyFile( const Nyx::CAString& privKeyFile )
{
    m_privKeyFile = privKeyFile;
}


/**
 *
 */
void NyxNetOSX::CSSLTcpIpSocket_Impl::SetPublicKeyFile( const Nyx::CAString& publicKeyFile )
{
    m_publicKeyFile = publicKeyFile;
}


/**
 *
 */
void NyxNetOSX::CSSLTcpIpSocket_Impl::SetDhKeyFile( const Nyx::CAString& dhKeyFile )
{
    m_dhKeyFile = dhKeyFile;
}


static int password_callback(char *buf, int size, int rwflag, void *password)
{
    strncpy(buf, "NyxWeb", size);
    buf[size - 1] = '\0';
    return(strlen(buf));
}


/**
 *
 */
void NyxNetOSX::CSSLTcpIpSocket_Impl::InitSSL()
{
    int res = 0;
    
    m_ctx = SSL_CTX_new(SSLv23_server_method());
    
    // Sets the default certificate password callback function. Read more under the Certificate Verification section.
    SSL_CTX_set_default_passwd_cb(m_ctx, password_callback);
    // Sets the certificate file to be used.
//    res = SSL_CTX_use_certificate_file(m_ctx, "/Users/dannyt/dev/WebServerTest/cert.pem", SSL_FILETYPE_PEM);
    res = SSL_CTX_use_certificate_file(m_ctx, m_publicKeyFile.c_str(), SSL_FILETYPE_PEM);

    // Sets the private key file to be used.
//    res = SSL_CTX_use_PrivateKey_file(m_ctx, "/Users/dannyt/dev/WebServerTest/privkey.pem", SSL_FILETYPE_PEM);
    res = SSL_CTX_use_PrivateKey_file(m_ctx, m_privKeyFile.c_str(), SSL_FILETYPE_PEM);

    
    // Load trusted root authorities
    //        res = SSL_CTX_load_verify_locations(m_ctx, "/Users/dannyt/dev/WebServerTest/rootCA.pem", 0);
    // Set the maximum depth to be used verifying certificates
    // Due to a bug, this is not enforced. The verify callback must enforce it.
    //        SSL_CTX_set_verify_depth(m_ctx, 1);
    // Set the certificate verification callback.
    //    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, verify_callback);
    
    // Load the random file, read 1024 << 10 bytes, add to PRNG for entropy
    //    RAND_load_file("random.pem", 1024 << 10);
    
    
    // We need to load the Diffie-Hellman key exchange parameters.
    // First load dh1024.pem (you DID create it, didn't you?)
//    BIO* bio = BIO_new_file("/Users/dannyt/dev/WebServerTest/dh1024.pem", "r");
    BIO* bio = BIO_new_file(m_dhKeyFile.c_str(), "r");
    // Did we get a handle to the file?
    //    if (bio == NULL) {
    //        printf("Couldn't open DH param file!\n");
    //        break;
    //    }
    
    // Read in the DH params.
    DH* ret = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
    // Free up the BIO object.
    BIO_free(bio);
    // Set up our SSL_CTX to use the DH parameters.
    if (SSL_CTX_set_tmp_dh(m_ctx, ret) < 0) {
        printf("Couldn't set DH parameters!\n");
        //        break;
    }
    
    // Now we need to generate a RSA key for use.
    // 1024-bit key. If you want to use something stronger, go ahead but it must be a power of 2. Upper limit should be 4096.
    RSA* rsa = RSA_generate_key(1024, RSA_F4, NULL, NULL);
    
    // Set up our SSL_CTX to use the generated RSA key.
    if (!SSL_CTX_set_tmp_rsa(m_ctx, rsa)) {
        printf("Couldn't set RSA key!\n");
        // We don't break out here because it's not a requirement for the RSA key to be set. It does help to have it.
    }
    // Free up the RSA structure.
    RSA_free(rsa);
    
    SSL_CTX_set_cipher_list(m_ctx, "ALL");
    // Set up our SSL object as before
    m_ssl = SSL_new(m_ctx);
    // Set up our BIO object to use the client socket
    
    NyxNet::CTcpIpSocket*   pTcpIpSocket = m_refSocket->TcpIpSocket();
    int socketid = pTcpIpSocket->TcpIpSocketId();
    
    m_bio = BIO_new_socket(socketid, BIO_NOCLOSE);
    BIO_set_nbio(m_bio, 0);
    SSL_set_bio(m_ssl, m_bio, m_bio);
    
    int r = SSL_accept(m_ssl);
    if ( r != 1 )
    {
        NYXTRACE(0x0, L"SSL accept failure");
    }
    else
    {
        NYXTRACE(0x0, L"SSL accept success");
    }
    
    if ( SSL_get_verify_result(m_ssl) != X509_V_OK)
    {
        NYXTRACE(0x0, L"ssl verify result failure");
    }
 
    m_bSSLOwner = true;
}

