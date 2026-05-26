#if defined(__has_include)
#  if __has_include(<httpd.h>) && __has_include(<http_config.h>)
#    define X402_HAVE_APACHE_HEADERS 1
#  endif
#endif

#ifdef X402_HAVE_APACHE_HEADERS

#include <http_config.h>
#include <http_log.h>

#include "../providers/stellar/stellar_provider.h"

extern "C" const x402_provider *x402_get_stellar_provider()
{
  return &x402_stellar_provider;
}

#else

extern "C" const void *x402_get_stellar_provider()
{
  return 0;
}

#endif
