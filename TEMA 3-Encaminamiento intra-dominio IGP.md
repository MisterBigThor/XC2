### TEMA 3 Encaminamiento intra-dominio IGP

#### MPLS: MultiProtocol Lable Switching

* Introducción y terminologia

  Es un protocolo para agilizar el proceso de consulta de las tablas de forwarding, dado que estas tablas tienen muchas entradas. Añadiendo MPLS hacemos el protocolo de encaminamiento mejor.

  En MPLS se usan etiquetas 'locales' entre parejas de routers para distribuir los prefijos, haciendo que los routers MPLS consulten una tabla de etiquetas de tamaño menor para reenviar paquetes MPLS. Un envio de paquetes con MPLS será: 

  * Se distribuyen las etiquetas dentro del sistema. 
  * El origen hace IP lookup para hacer *label push* para añadir la cabecera.
  * Los intermedios hacen *label swap* con su label local en la cabecera.
  * En el destino, se quita la cabecera MPLS ,*label pop* , y se hace IP lookup para ver el gw.

  Los router que entienden MPLS son <u>L</u>abel <u>S</u>withc <u>R</u>outer y generan una vez distribuidas las etiquetas Label Switched Path, que es un camino entre un ingress E-Label Edge Router y un egress E-LSR. La logica de forwarding esta en el data plane.

* Formato Etiqueta

  * Las etiquetas se proporcionan en sentido *Upstream* y los paquetes circulan en sentido *Downstream*.
  * La cabecera MPLS se sitúan entre el paquete IP y el paquete TCP (nivel 2,5) y contiene el tag, un TTL y 1 bit S que indica si hay label stack. 

* Tablas MPLS


![tMPLS](tablasMPLS)

​	(p.e. OSPF o RIP como protocolos de routing y LDP o RSVP para distribuir etiquetas.)

* **L**abel **D**istribution **P**rotocol

  Funciona entre dos LSR adyacentes por conexión TCP (el RID + alto sera el que abra la conexión -> active). 

  1. El active enviara init con parámetros de configuración(keepAlive, MTU, método).
  2. Se envian los tags correspondientes.
  3. Cada cierto tiempo, se envía un keepalive.

  Los métodos pueden ser No solicitado o Bajo petición.

* Penultimate Hop Hopping (PHP)
* Label Stack



#### LDP: Label Distribution Protocol

#### MPLS-TE: MPLS Traffic Enginiering

#### MPLS Fast Reroute

