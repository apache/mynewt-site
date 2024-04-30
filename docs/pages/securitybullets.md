
### Security through the life of a device

One of the primary goals of the Apache Mynewt project is to facilitate security assurance at every stage of a product's lifecycle. Securing a device essentially requires balancing the cost of the product inclusive of all its security mechanisms and the value of the product, keeping in mind that neither should exceed the cost of attacks on deployments of that product. Apache Mynewt OS takes care of the fundamental security requirements of a connected embedded device in a commercial marketplace. It also acknowledges that security is an ongoing effort with evolving threat scenarios, and therefore enables remote, secure updates over the product's lifetime.

| Stage         | Secure Feature/Service                                                                                                                             |
|---------------|----------------------------------------------------------------------------------------------------------------------------------------------------|
| Development   | Dev image signing and verification <br> Separation of duties <br> Enable HW security (e.g. crypto accelerator) <br> Enable security logs and stats |
| Manufacturing | Unique Device ID <br> Unique Crypto keys <br> Secure bootloader <br> Manufacturing data integrity                                                  |
| Deployment    | Prod image signing and verification <br> Authenticated and authorized network join <br> Secure manufacturing data upload <br> Secure time update   |
| Operations    | Authorized access to device <br> Mutual authentication <br> Encrypted communication <br> Data integrity <br> Secure over-the-air updates           |
| Decommission  | Authorized credential removal                                                                                                                      |