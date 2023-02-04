
IF ( NOT CBS_BUILD )
	# Add your "normal" cmake build stuff here. That is if you use cmake for your prject
	# Most automake based projects will just leave this blank

ELSE ( NOT CBS_BUILD )	
	# --- CBS build ---
	project ( simpleCommandLine )
	include ( $ENV{CBS_ROOT_DIR}/cbs_common_rules.cbs )
	BUILD_EXECUTABLE ( simpleCommandLine ) 
ENDIF ( NOT CBS_BUILD )
