### TEMA 3 Encaminamiento intra-dominio IGP

#### MPLS: MultiProtocol Lable Switching

* Introducción y terminologia

  Es un protocolo para agilizar el proceso de consulta de las tablas de forwarding, dado que estas tablas tienen muchas entradas. Añadiendo MPLS hacemos el protocolo de encaminamiento mejor.

  En MPLS se usan etiquetas 'locales' entre parejas de routers para distribuir los prefijos, haciendo que los routers MPLS consulten una tabla de etiquetas de tamaño menor para reenviar paquetes MPLS. Un envio de paquetes con MPLS será: 

  * Se distribuyen las etiquetas dentro del sistema. 
  * El origen hace IP lookup para hacer *label push* para añadir la cabecera.
  * Los intermedios hacen *label swap* con su label local en la cabecera.
  * En el destino, se quita la cabecera MPLS ,*label pop* , y se hace IP lookup para ver el gw.

  Los router que entienden MPLS son <u>L</u>abel <u>S</u>witch <u>R</u>outer y generan una vez distribuidas las etiquetas Label Switched Path, que es un camino entre un ingress E-Label Edge Router y un egress E-LSR. La logica de forwarding esta en el data plane.

* Formato Etiqueta

  * Las etiquetas se proporcionan en sentido *Upstream* y los paquetes circulan en sentido *Downstream*.
  * La cabecera MPLS se sitúan entre el paquete IP y el paquete TCP (nivel 2,5) y contiene el tag, un TTL y 1 bit S que indica si hay label stack. 

* Tablas MPLS


![tMPLS](tablasMPLS)

​	(p.e. OSPF o RIP como protocolos de routing y LDP o RSVP para distribuir etiquetas.)

#### LDP: Label Distribution Protocol

Funciona entre dos LSR adyacentes por conexión TCP (el RID + alto sera el que abra la conexión -> active). 

1. El active enviara init con parámetros de configuración(keepAlive, MTU, método).
2. Se envian los tags correspondientes.
3. Cada cierto tiempo, se envía un keepalive.

El método por defecto es no solicitado, pero puede ser bajo petición.

* No solicitado: El LSR distribuye la associacion tag/prefijo en upstream.

* Bajo petición: El LSR le indica al LSR 'propietario' del prefijo que elija una etiqueta; el propietario seleciona una etiqueta y la envia al LSR.

#### 

#### Ejemplo Funcionamiento Básico

![funcionamiento MPLS](mplsE1)

##### Mejoras MPLS: Penultimate Hop Hopping (PHP)

Para ahorrarse un label swap, se puede adelantar el pop en el penúltimo LSR. Por defecto PHP esta activado.

![phpExample](php)

##### Mejora MPLS: Label Stack

Los Label Swithching Paths pueden ser visto como tuneles, ya que los paquetes quedan escondidos dentro de MPLS, facilitando construir VPN's. Además es multiprotocolo.

Se pueden encapsular redes MPLS dentro de otras redes MPLS(campo S de la cabecera):

![labelStack](C:\Users\corre\Documents\FIB Q7\XC2\XC2\mplsLabelStack)



#### MPLS-TE: MPLS Traffic Engineering

En una estructura normal con coste OSPF tiene costes estáticos, haciendo que parte de los recursos no se utilicen.

La Ingeniería de tráfico optimiza esto, moviendo el tráfico donde hay recursos; para ello hay que usar costes que varien con el tiempo y la carga de trabajo.

Se usan extensiones para OSPF, MPLS y RSVP(LDP de cisco) más una clase de algoritmos de encaminamiento basados en constrains (CBR).

#### MPLS Fast Reroute

