# copy the python nautilus plugin to build dir as it is going to
# be changed.
if( UNIX AND NOT APPLE )

    configure_file(syncstate.py syncstate.py COPYONLY)

    # Call the setupappname.sh script to set the custom app name.
    set (cmd "${CMAKE_CURRENT_SOURCE_DIR}/setappname.sh")
    execute_process(COMMAND ${cmd} ${APPLICATION_SHORTNAME}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    ERROR_VARIABLE errors OUTPUT_VARIABLE out)

    # Create a nemo plugin script from the nautilus one. 
    # nemocmd copies the syncstate.py and performs string replacement.
    set (nemocmd "${CMAKE_CURRENT_SOURCE_DIR}/createnemoplugin.sh")
    execute_process(COMMAND ${nemocmd}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    ERROR_VARIABLE errors OUTPUT_VARIABLE out)

    # Create a caja plugin script from the nautilus one. 
    # cajacmd copies the syncstate.py and performs string replacement.
    set (cajacmd "${CMAKE_CURRENT_SOURCE_DIR}/createcajaplugin.sh")
    execute_process(COMMAND ${cajacmd}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    ERROR_VARIABLE errors OUTPUT_VARIABLE out)

                                        
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/syncstate.py DESTINATION ${CMAKE_INSTALL_DATADIR}/nautilus-python/extensions RENAME syncstate-${APPLICATION_SHORTNAME}.py)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/syncstate_nemo.py DESTINATION ${CMAKE_INSTALL_DATADIR}/nemo-python/extensions RENAME syncstate-${APPLICATION_SHORTNAME}.py)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/syncstate_caja.py DESTINATION ${CMAKE_INSTALL_DATADIR}/caja-python/extensions RENAME syncstate-${APPLICATION_SHORTNAME}.py)
    
    # Set permissions for the install_nextcloud_extension.sh script
    set(INSTALL_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/install_nextcloud_extension.sh")
    file(CHMOD ${INSTALL_SCRIPT} PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)

    # Add custom command to install the Nextcloud Nautilus extension
    add_custom_target(install_nextcloud_extension ALL
                      COMMAND ${INSTALL_SCRIPT}
                      COMMENT "Installing Nextcloud Nautilus extension")
endif()

