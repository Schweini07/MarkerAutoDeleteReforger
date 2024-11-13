[BaseContainerProps(configRoot: true)]
class MAD_Config
{
	[Attribute(defvalue: "3600.0", desc: "The time in seconds after which a marker will delete itself")]
	float m_fAutoDeleteDurationInSeconds;
	
	[Attribute(defvalue: "true", desc: "Determines if the opacity of a marker will lessen over its lifetime")]
	bool m_bChangeOpacityDuringLifetime;
}