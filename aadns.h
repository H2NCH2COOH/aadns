/***
 * AADNS: Another Asynchronous DNS resolving library
 * The purpose of this library is to provide the following functionalities:
 *   1. Asynchronous DNS resolve over UDP & TCP
 *   2. Asynchronous DNS resolve over SOCKS5
 * This library does not support DNSSEC
 */

#ifndef _AADNS_H_
#define _AADNS_H_

#include <stdint.h>
#include <netinet/in.h>

typedef struct AADNSHandle_s AADNSHandle;
typedef struct AADNSResolver_s AADNSResolver;

/***
 * Create a new handle pointer
 * Each handle must be used only in one thread
 * The handle needs to be freed using AADNS_free_handle()
 * @return On success: the handle pointer
 *         On failure: NULL
 */
AADNSHandle* AADNS_new_handle();

/***
 * Free a handle
 * This function will cancel all on going resolves and will block until all
 * related resources are freed
 */
void AADNS_free_handle(AADNSHandle* handle);

/***
 * Create a new resolver
 * The created reslover should be freed by AADNS_free_resolver()
 * AADNS_set_resolver_opt_*() functions can be used to set options on the
 * created resolver
 * Once a resolver is used to resolve, it can not be modified any more
 * @param addr The address of the resolver (acceptable by sendto())
 * @param addr_len The length of the address
 * @return On success: the resolver pointer
 *         On failure: NULL
 */
AADNSResolver* AADNS_new_resolver(struct sockaddr_in* addr, size_t addr_len);

/***
 * Free a resolver
 * This function will fail when the resolver is currently used
 * @param The reslover to free
 * @return On success: 0
 *         On failure: an error number
 */
int AADNS_free_resolver(AADNSResolver* resolver);

/***
 * Set the source address to bind when sending DNS request to this resolver
 * @param resolver The resolver
 * @param addr The address to bind
 * @param addr_len The length of the address
 * @return On success: 0
 *         On failure: an error number
 */
int AADNS_set_resolver_opt_bind_to(AADNSResolver* resolver, struct sockaddr_in* addr, size_t addr_len);
int AADNS_set_resolver_opt_over_socks5(AADNSResolver* resolver, struct sockaddr_in* addr, size_t addr_len);
int AADNS_setresolver_opt_EDNS0(AADNSResolver* resolver, size_t size);



#endif /* _AADNS_H_ */
