function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtDW"] = {file: "C:\\Users\\LSC\\Desktop\\rtos-can-dc-motor-control\\01_STM32\\01_DC_matlab(simulink)\\Subsystem_ert_rtw\\Subsystem.c",
	size: 72};
	 this.metricsArray.var["rtM_"] = {file: "C:\\Users\\LSC\\Desktop\\rtos-can-dc-motor-control\\01_STM32\\01_DC_matlab(simulink)\\Subsystem_ert_rtw\\Subsystem.c",
	size: 277};
	 this.metricsArray.var["rtU"] = {file: "C:\\Users\\LSC\\Desktop\\rtos-can-dc-motor-control\\01_STM32\\01_DC_matlab(simulink)\\Subsystem_ert_rtw\\Subsystem.c",
	size: 16};
	 this.metricsArray.var["rtY"] = {file: "C:\\Users\\LSC\\Desktop\\rtos-can-dc-motor-control\\01_STM32\\01_DC_matlab(simulink)\\Subsystem_ert_rtw\\Subsystem.c",
	size: 8};
	 this.metricsArray.fcn["Subsystem_initialize"] = {file: "C:\\Users\\LSC\\Desktop\\rtos-can-dc-motor-control\\01_STM32\\01_DC_matlab(simulink)\\Subsystem_ert_rtw\\Subsystem.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["Subsystem_step"] = {file: "C:\\Users\\LSC\\Desktop\\rtos-can-dc-motor-control\\01_STM32\\01_DC_matlab(simulink)\\Subsystem_ert_rtw\\Subsystem.c",
	stack: 52,
	stackTotal: 52};
	 this.metricsArray.fcn["memcpy"] = {file: "C:\\Program Files\\MATLAB\\R2016a\\sys\\lcc\\include\\string.h",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data;}
}
	 CodeMetrics.instance = new CodeMetrics();
