# Encaminamiento Inter-dominio EGP

Internet está formado por diferentes Sistemas Autónomos interconectados, para encaminar estos diferentes sistemas, entre ellos, se utilizan protocolos Exterior Gateway Protocol. En concreto veremos BGP; él usado en Internet, que está basado en vector-distancia.

### Border Gateway Protocol

* Cada camino se construye como composición de próximo salto, el conocimiento de cada router depende de su router informante.
* El encaminamiento puede estar basado en políticas sobre atributos.
* Permite no compartir información confidencial de cada AS.
* Entre dos routers frontera de un AS(BGP peers), se establece una sesión TCP donde comparte la información de encaminamiento de cada *prefijo* con sus atributos.

### External/Internal BGP

La información que un AS recibe debe ser retransmitida por todos sus routers frontera, sin variar el contenido de este mensaje de encaminamiento. Todos los BGP peers de un AS deben tener una sesión BGP entre ellos, dando lugar a una full mesh.

![imageBGP](t4BGP1.jpg)

Los mensajes de iBGP son tratados como paquetes IP y retransmitidos normalmente .Los mensaje de iBGP y de eBGP son identicos.

Se debe usar una **interfaz virtual para los iBGP** y una **interfaz real para eBGP**.

Si es iBGP con una interfaz real cae la sesión BGP, en cambio si se usa una interfaz virtual el protocolo de encaminamiento interno encontrara una nueva ruta y no caera esta sesión TCP. En el caso de eBGP debemos ver cuando se pierde una interfaz real entre AS.

### Sesión BGP

Se utiliza TCP (port 179), iniciando la conexión con el three-way handshaking para establecer la conexión TCP. Una vez establecido el TCP y abierto el canal BGP se mandan los prefijos que que cada AS conoce, y quiere compartir. Las rutas BGP no tienen un tiempo de vida. Los updates BGP pueden enviar updates quitando rutas (withdraw).

Los estados por los que pasa la sesión BGP son:

idle :arrow_right: connect :arrow_right:TCP Established :arrow_right: BGP open :arrow_right:Envio de updates

Si hay time-out en el estado connect, se pasa a estado active.

### Base de datos BGP

Un router BGP mantiene 3 BD con diferente información.

* Adj-RIB_In: Todos los prefijos y atributos recibidos por sus peers.

* Loc_RIB: Contiene la información de encaminamiento local, selecionando a través de su politica de encaminamiento.

  Con esta información se genera la tabla de encaminamiento.

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

### Atributos BGP

  Los atributos que se añaden a los mensajes de update son diversos, algunos son obligatorios:

  * AS-PATH: Secuencia de números de AS por donde ha pasado un prefijo. Se usa para evitar bucles en las notificaciones de prefijos y para determinar el camino más corto (menor número de AS)

  * Next-hop: Indica la @IP del router que hace de GW entre AS. Es el GW a nivel de AS.

    ![ejemploBGPnextHop](tBGP2.jpg)

  * Next-hop third-party: Caso que haya un enlace directo sin sesión eBGP, sin next-hop los datagramas pasarían por un tercer AS.

  * Next-hop backdoor: Desacoplo del router BGP del router que procesa paquetes.

  * ORIGIN: Determina como se ha aprendido un prefijo. Se añade al final del AS-PATH. Puede ser un '?' si esta información está incompleta, una 'i' si se ha aprendido por IGP o una 'e' si se ha aprendido por EGP (protocolo ya no utilizado de encaminamiento inter-AS).

Otros atributos son opcionales:

* Aggregator: Si un router sumariza prefijos se utiliza este atributo para indicar el RID del router y el AS donde se ha hecho.
* Local preference: Se utiliza para manipular la selección del mejor camino, se escoge la ruta con valor mas alto. Por defecto el valor es 100.
* Multi Exit Discriminator/MED/Metric: Se elige la ruta con <u>metric</u> más bajo. Los AS pueden recomendar al vecino cual usar, pero este puede elegir. Por defecto el valor es 0.

### Algoritmo de Selección BGP

Hay varios casos donde existen varias rutas para llegar a un destino y se establece un orden para los diferentes atributos BGP.

### Políticas sobre BGP [COMPLETAR]

SCRIPTS CISCO:  

Si en la access-list no aparece un prefijo, por defecto se filtra (no aparece en la tabla de encaminamiento, si en la de ADJRIB_In). En caso de querer usarlo, añadir un rout-map que acepte todo lo demás.

[EJEMPLO POL2]

### Escenarios Comunes en Internet

* Stub

  AS cliente, conectado a otro AS que le proporciona transito. En este caso se puede utilizar un numero de AS privado, sin pasar por IANA (hay traducción en el caso de que el AS quiera ir a Internet, donde solo caben los números AS públicos).

  La tabla del BR del AS Stub, tendrá una ruta por defecto al router del AS provider

* Stub multi-homed

  AS con 2 o más conexiones, por seguridad, a un mismo AS (proveedor). Es posible que existan varios BR en cada frontera del AS.

  [TODO:review this!]

  Existen varias configuraciones posibles:

  * <u>1 conexion eBGP, otras preparadas</u>, entonces el router anuncia sus redes internas solamente a su BGP peer. Solo configura una ruta por defecto a este router. Si falla, se abre la otra sesión.
  * <u>Una conexión preferida, otras de backup abiertas siempre</u>. Usando MET para marcar la preferida y compartiendo los prefijos con todos los BGP peers.
  * Hacer <u>balanceo de carga</u> usando los 2 o más routers. Dividiendo el anuncio de la mitad de los prefijos del Stub; en el otro sentido haciendo lo mismo pero general a todas las direcciones posibles.

* Multi-homed

  AS que no proporciona tránsito, tiene 2 o más conexiones con diferentes AS proveedores, siendo él un cliente.

  La configuración es igual que en Stub multi-homed, pero el router no debe dar transito entre los AS proveedores de forma explicita.

* Transito

  AS que tiene 2 o más conexiones con otros AS y proporciona transito entre ellos, según el contrato con los vecinos.

### Route leaks

[COMPLETAR]
