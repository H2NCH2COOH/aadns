/***
 * AADNS: Another Asynchronous DNS resolving library
 * The purpose of this library is to provide the following functionalities:
 *   1. Asynchronous DNS resolve over UDP & TCP
 *   2. Asynchronous DNS resolve over SOCKS5 (TCP only)
 *   3. Optional DNS over TLS
 * This library does not support DNSSEC
 */

#ifndef _AADNS_H_
#define _AADNS_H_

#include <stdint.h>
#include <netinet/in.h>

typedef struct AADNSHandle_s AADNSHandle;
typedef struct AADNSResolver_s AADNSResolver;

/***
 * Create a new handle
 * Each handle must be used only in one thread
 * The handle needs to be freed using AADNS_free_handle()
 * @return                  Success: the handle pointer
 *                          Failure: NULL
 */
AADNSHandle* AADNS_new_handle();

/***
 * Free a handle
 * This function will cancel all on going resolves and will block until all
 * related resources are freed
 * @param handle            The handle to free
 */
void AADNS_free_handle(AADNSHandle* handle);

#define DNS_DEFAULT_PORT            53
#define DNS_OVER_TLS_DEFAULT_PORT   853

#define AADNS_RESOLVER_UDP          1
#define AADNS_RESOLVER_TCP          2
#define AADNS_RESOLVER_TLS          6 //Implying TCP

/***
 * Create a new resolver
 * The created reslover should be freed by AADNS_free_resolver()
 * AADNS_set_resolver_opt_*() functions can be used to set options on the
 * created resolver
 * Once a resolver is used to resolve, it can not be modified any more
 * @param addr              The address of the resolver (acceptable by sendto())
 * @param addr_len          The length of the address
 * @param flags             Flags AADNS_RESOLVER_* ORed
 * @return                  Success: the resolver pointer
 *                          Failure: NULL
 */
AADNSResolver* AADNS_new_resolver(struct sockaddr_in* addr, size_t addr_len, int flags);

/***
 * Free a resolver
 * This function will fail when the resolver is currently used
 * @param                   The reslover to free
 * @return                  Success: 0
 *                          Failure: an error number
 */
int AADNS_free_resolver(AADNSResolver* resolver);

/***
 * Set the source address to bind when sending DNS request to this resolver
 * @param resolver The resolver
 * @param addr              The address to bind
 * @param addr_len          The length of the address
 * @return                  Success: 0
 *                          Failure: an error number
 */
int AADNS_set_resolver_opt_bind_to(AADNSResolver* resolver, struct sockaddr_in* addr, size_t addr_len);

/***
 * Set the SOCKS5 server address to use when sending DNS request to this resolver
 * Only available to TCP
 */
int AADNS_set_resolver_opt_over_socks5(AADNSResolver* resolver, struct sockaddr_in* addr, size_t addr_len);



#endif /* _AADNS_H_ */
