# Encaminamiento Inter-dominio EGP

Internet está formado por diferentes Sistemas Autonomos interconectados, para encaminar estos diferentes sistemas, entre ellos, se utilizan protocolos Exterior Gateway Protocol. En concreto veremos BGP; él usado en Internet, que está basado en vector-distancia.

### Border Gateway Protocol

* Cada camino se construye como composición de próximo salto, el conocimiento de cada router depende de su router informante.
* El encaminamiento puede estar basado en políticas sobre atributos.
* Permite no compartir información confidencial de cada AS.
* Entre dos routers frontera de un AS(BGP peers), se establece una sesión TCP donde comparte la información de encaminamiento de cada *prefijo* con sus atributos.

### External/Internal BGP

La información que un AS recibe debe ser retransmitida por todos sus routers frontera, sin variar el contenido de este mensaje de encaminamiento. Todos los BGP peers de un AS deben tener una sesión BGP entre ellos, dando lugar a una full mesh.

![image-20191118214705778](D:\FIBQ7\XC2\t4BGP1)

Los mensajes de iBGP son tratados como paquetes IP y retransmitidos normalmente .Los mensaje de iBGP y de eBGP son identicos. 

Se debe usar una **interfaz virtual para los iBGP** y una **interfaz real para eBGP**. 

Si es iBGP con una interfaz real cae la sesión BGP, en cambio si se usa una interfaz virtual el protocolo de encaminamiento interno encontrara una nueva ruta y no caera esta sesión TCP. En el caso de eBGP debemos ver cuando se pierde una interfaz real entre AS.

### Sesión BGP

Se utiliza TCP (port 179), iniciando la conexión con el three-way handshaking para establecer la conexión TCP. Una vez establecido el TCP y abierto el canal BGP se mandan los prefijos que que cada AS conoce, y quiere compartir. Las rutas BGP no tienen un tiempo de vida. Los updates BGP pueden enviar updates quitando rutas (withdraw). 

### Base de datos BGP

Un router BGP mantiene 3 BD con diferente información.

* Adj-RIB_In: Todos los prefijos y atributos recibidos por sus peers.
* Loc_RIB: Contiene la información de encaminamiento local, selecionando a través de su politica de encaminamiento. Con esta información se genera la tabla de encaminamiento.
* Adj-RIB_Out: Todos los prejifos y atributos que este router anuncia a sus peers. Puede ser diferente según el vecino.

### Mensajes BGP

Existe una cabecera común de 19 bytes y según el type se añaden los campos necesarios.

Marker: Seguridad, Lenght: Longitud BGP(cabecera + payload) y Type: (Open, Update, Notification, Keepalive).

* Open

  En los mensajes open se negocian los parámetros y se identifican los AS. Añade a la cabecera común la <u>versión</u> (v4), el numero de <u>AS</u>, el <u>BGPid</u> (RID del router), el <u>Hold Timer</u>, y las <u>opciones</u>.

  El Hold timer, entre 0 y 60 es el tiempo entre UPDATE o KEEPALIVE. Se esperan 3 HoldTimer antes de cerrar las sesión TCP. Se usa el menor de los dos propuestos. 0 no se usa esto. El campo de opciones añade otras capacidades.

* KeepAlive

  Se usa para verificar la conectividad entre dos peers. Se envia la cabecera común de 19 bytes.

* Notification

  Sobre un error en la sesión BGP, se envia este mensaje y se cierra la sesión TCP. Se añade un numero de error, un subcodigo y se añade en el campo data el mensaje que ha provocado el error.

* Update

  Se comparte información de encaminamiento entre peers, con los siguientes campos:

  Withdraw routes: Notifica que un prefijo ya no es valido

  Path Attribute: Atributos comunes de los NLRI del update (si no hay atributos comunes se debe separar el mensaje de update). Hay varios atributos estandar usados (ORIGEN, AS_PATH, NEXT HOP, ...).

  El Network Layer Reachability Information (NLRI) contiene la lista de prefijos anunciados por este peer, limitado por el tamaño maximo del mensaje BGP 4096 bytes.

  Se añaden 2 bytes para la longitud del estos campos. La longuitud del NLRI es el restante.

