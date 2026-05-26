CC ?= cc
CXX ?= c++
PKG_CONFIG ?= pkg-config
CRYPTO_CFLAGS := $(shell $(PKG_CONFIG) --cflags openssl libsodium 2>/dev/null)
CRYPTO_LIBS := $(shell $(PKG_CONFIG) --libs openssl libsodium 2>/dev/null)
REPO_INCLUDES := -I. -I.. -Iproviders/stellar -Iproviders/stellar/schemas
THIRD_PARTY_INCLUDES := -Ithird_party
CFLAGS ?= -Wall -Wextra -Werror -std=c11
CXXFLAGS ?= -Wall -Wextra -Werror -Wno-unused-parameter -std=c++17 $(REPO_INCLUDES) $(THIRD_PARTY_INCLUDES) $(CRYPTO_CFLAGS)
LDFLAGS ?=
LIBS ?= -lcurl $(CRYPTO_LIBS)

CORE_OBJS = core/x402_core.o
PROVIDER_OBJS = providers/stellar/stellar_provider.o
APACHE_OBJS = core/x402_core.apache.o providers/stellar/stellar_provider.apache.o apache/mod_x402.apache.o
APACHE_SO = apache/.libs/mod_x402.so

all: $(CORE_OBJS) $(PROVIDER_OBJS)

check-build: $(CORE_OBJS) $(PROVIDER_OBJS)

core/x402_core.o: core/x402_core.c core/x402_provider.h
	$(CC) $(CFLAGS) $(REPO_INCLUDES) -c -o $@ core/x402_core.c

providers/stellar/stellar_provider.o: providers/stellar/stellar_provider.cpp providers/stellar/stellar_provider.h core/x402_provider.h
	$(CXX) $(CXXFLAGS) -c -o $@ providers/stellar/stellar_provider.cpp

clean:
	rm -f $(CORE_OBJS) $(PROVIDER_OBJS) $(APACHE_OBJS) $(APACHE_SO)
	rm -rf apache/.libs

distclean: clean
	rm -rf examples/node_modules examples/.demo-accounts examples/.demo-artifacts
