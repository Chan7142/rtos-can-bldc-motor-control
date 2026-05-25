function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <S1>/Discrete State-Space */
	this.urlHashMap["DC_M_sim:21"] = "Subsystem.c:50,99&Subsystem.h:42";
	/* <S1>/Gain */
	this.urlHashMap["DC_M_sim:10"] = "Subsystem.c:58";
	/* <S1>/Saturation */
	this.urlHashMap["DC_M_sim:27"] = "Subsystem.c:89,98";
	/* <S1>/Scope */
	this.urlHashMap["DC_M_sim:23"] = "msg=rtwMsg_reducedBlock&block=DC_M_sim:23";
	/* <S1>/Scope1 */
	this.urlHashMap["DC_M_sim:25"] = "msg=rtwMsg_reducedBlock&block=DC_M_sim:25";
	/* <S1>/Scope2 */
	this.urlHashMap["DC_M_sim:26"] = "msg=rtwMsg_reducedBlock&block=DC_M_sim:26";
	/* <S1>/Sum */
	this.urlHashMap["DC_M_sim:8"] = "Subsystem.c:57";
	/* <S1>/Sum1 */
	this.urlHashMap["DC_M_sim:9"] = "Subsystem.c:44";
	/* <S2>/Derivative Gain */
	this.urlHashMap["DC_M_sim:7:1668"] = "Subsystem.c:70";
	/* <S2>/Integral Gain */
	this.urlHashMap["DC_M_sim:7:1667"] = "Subsystem.c:66";
	/* <S2>/Integrator */
	this.urlHashMap["DC_M_sim:7:1669"] = "Subsystem.c:65,121&Subsystem.h:43";
	/* <S2>/Proportional Gain */
	this.urlHashMap["DC_M_sim:7:1666"] = "Subsystem.c:62";
	/* <S2>/Sum */
	this.urlHashMap["DC_M_sim:7:1665"] = "Subsystem.c:80";
	/* <S3>/DTDup */
	this.urlHashMap["DC_M_sim:7:1675"] = "msg=rtwMsg_reducedBlock&block=DC_M_sim:7:1675";
	/* <S3>/Diff */
	this.urlHashMap["DC_M_sim:7:1674"] = "Subsystem.c:82";
	/* <S3>/TSamp */
	this.urlHashMap["DC_M_sim:7:1672"] = "Subsystem.c:73,75";
	/* <S3>/UD */
	this.urlHashMap["DC_M_sim:7:1673"] = "Subsystem.c:81,124&Subsystem.h:44";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "Subsystem"};
	this.sidHashMap["Subsystem"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "DC_M_sim:13"};
	this.sidHashMap["DC_M_sim:13"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "DC_M_sim:7"};
	this.sidHashMap["DC_M_sim:7"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<S3>"] = {sid: "DC_M_sim:7:1670"};
	this.sidHashMap["DC_M_sim:7:1670"] = {rtwname: "<S3>"};
	this.rtwnameHashMap["<S1>/theta"] = {sid: "DC_M_sim:14"};
	this.sidHashMap["DC_M_sim:14"] = {rtwname: "<S1>/theta"};
	this.rtwnameHashMap["<S1>/speed_rad"] = {sid: "DC_M_sim:16"};
	this.sidHashMap["DC_M_sim:16"] = {rtwname: "<S1>/speed_rad"};
	this.rtwnameHashMap["<S1>/ref"] = {sid: "DC_M_sim:29"};
	this.sidHashMap["DC_M_sim:29"] = {rtwname: "<S1>/ref"};
	this.rtwnameHashMap["<S1>/Demux"] = {sid: "DC_M_sim:24"};
	this.sidHashMap["DC_M_sim:24"] = {rtwname: "<S1>/Demux"};
	this.rtwnameHashMap["<S1>/Discrete PID Controller"] = {sid: "DC_M_sim:7"};
	this.sidHashMap["DC_M_sim:7"] = {rtwname: "<S1>/Discrete PID Controller"};
	this.rtwnameHashMap["<S1>/Discrete State-Space"] = {sid: "DC_M_sim:21"};
	this.sidHashMap["DC_M_sim:21"] = {rtwname: "<S1>/Discrete State-Space"};
	this.rtwnameHashMap["<S1>/Gain"] = {sid: "DC_M_sim:10"};
	this.sidHashMap["DC_M_sim:10"] = {rtwname: "<S1>/Gain"};
	this.rtwnameHashMap["<S1>/Mux"] = {sid: "DC_M_sim:22"};
	this.sidHashMap["DC_M_sim:22"] = {rtwname: "<S1>/Mux"};
	this.rtwnameHashMap["<S1>/Saturation"] = {sid: "DC_M_sim:27"};
	this.sidHashMap["DC_M_sim:27"] = {rtwname: "<S1>/Saturation"};
	this.rtwnameHashMap["<S1>/Scope"] = {sid: "DC_M_sim:23"};
	this.sidHashMap["DC_M_sim:23"] = {rtwname: "<S1>/Scope"};
	this.rtwnameHashMap["<S1>/Scope1"] = {sid: "DC_M_sim:25"};
	this.sidHashMap["DC_M_sim:25"] = {rtwname: "<S1>/Scope1"};
	this.rtwnameHashMap["<S1>/Scope2"] = {sid: "DC_M_sim:26"};
	this.sidHashMap["DC_M_sim:26"] = {rtwname: "<S1>/Scope2"};
	this.rtwnameHashMap["<S1>/Sum"] = {sid: "DC_M_sim:8"};
	this.sidHashMap["DC_M_sim:8"] = {rtwname: "<S1>/Sum"};
	this.rtwnameHashMap["<S1>/Sum1"] = {sid: "DC_M_sim:9"};
	this.sidHashMap["DC_M_sim:9"] = {rtwname: "<S1>/Sum1"};
	this.rtwnameHashMap["<S1>/input"] = {sid: "DC_M_sim:28"};
	this.sidHashMap["DC_M_sim:28"] = {rtwname: "<S1>/input"};
	this.rtwnameHashMap["<S2>/u"] = {sid: "DC_M_sim:7:1"};
	this.sidHashMap["DC_M_sim:7:1"] = {rtwname: "<S2>/u"};
	this.rtwnameHashMap["<S2>/Derivative Gain"] = {sid: "DC_M_sim:7:1668"};
	this.sidHashMap["DC_M_sim:7:1668"] = {rtwname: "<S2>/Derivative Gain"};
	this.rtwnameHashMap["<S2>/Differentiator"] = {sid: "DC_M_sim:7:1670"};
	this.sidHashMap["DC_M_sim:7:1670"] = {rtwname: "<S2>/Differentiator"};
	this.rtwnameHashMap["<S2>/Integral Gain"] = {sid: "DC_M_sim:7:1667"};
	this.sidHashMap["DC_M_sim:7:1667"] = {rtwname: "<S2>/Integral Gain"};
	this.rtwnameHashMap["<S2>/Integrator"] = {sid: "DC_M_sim:7:1669"};
	this.sidHashMap["DC_M_sim:7:1669"] = {rtwname: "<S2>/Integrator"};
	this.rtwnameHashMap["<S2>/Proportional Gain"] = {sid: "DC_M_sim:7:1666"};
	this.sidHashMap["DC_M_sim:7:1666"] = {rtwname: "<S2>/Proportional Gain"};
	this.rtwnameHashMap["<S2>/Sum"] = {sid: "DC_M_sim:7:1665"};
	this.sidHashMap["DC_M_sim:7:1665"] = {rtwname: "<S2>/Sum"};
	this.rtwnameHashMap["<S2>/y"] = {sid: "DC_M_sim:7:10"};
	this.sidHashMap["DC_M_sim:7:10"] = {rtwname: "<S2>/y"};
	this.rtwnameHashMap["<S3>/U"] = {sid: "DC_M_sim:7:1671"};
	this.sidHashMap["DC_M_sim:7:1671"] = {rtwname: "<S3>/U"};
	this.rtwnameHashMap["<S3>/DTDup"] = {sid: "DC_M_sim:7:1675"};
	this.sidHashMap["DC_M_sim:7:1675"] = {rtwname: "<S3>/DTDup"};
	this.rtwnameHashMap["<S3>/Diff"] = {sid: "DC_M_sim:7:1674"};
	this.sidHashMap["DC_M_sim:7:1674"] = {rtwname: "<S3>/Diff"};
	this.rtwnameHashMap["<S3>/TSamp"] = {sid: "DC_M_sim:7:1672"};
	this.sidHashMap["DC_M_sim:7:1672"] = {rtwname: "<S3>/TSamp"};
	this.rtwnameHashMap["<S3>/UD"] = {sid: "DC_M_sim:7:1673"};
	this.sidHashMap["DC_M_sim:7:1673"] = {rtwname: "<S3>/UD"};
	this.rtwnameHashMap["<S3>/Y"] = {sid: "DC_M_sim:7:1676"};
	this.sidHashMap["DC_M_sim:7:1676"] = {rtwname: "<S3>/Y"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
