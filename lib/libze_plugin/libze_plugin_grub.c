#include "libze_plugin/libze_plugin_grub.h"

#include "libze/libze.h"
#include "libze/libze_util.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGEX_BUFLEN 512
#define GRUB_ENTRY_PREFIX "org.zectl"

libze_error
update_grub() {
    libze_error ret;
    int ret_grub = system("update-grub >/dev/null 2>&1");
    if (ret_grub != 0) {
        ret = LIBZE_ERROR_UNKNOWN;
    } else {
        ret = LIBZE_ERROR_SUCCESS;
    }

    return ret;
}


/********************************************************************
 ********************** Plugin initialization ***********************
 ********************************************************************/

/**
 * @brief Initialize the grub plugin
 *
 * @param[in,out] lzeh  libze handle
 *
 * @pre lzeh->ze_props is allocated
 *
 * @return @p LIBZE_ERROR_SUCCESS on success,
 *         @p LIBZE_ERROR_UNKNOWN
 */
libze_error
libze_plugin_grub_init(libze_handle *lzeh) {
    libze_error ret = LIBZE_ERROR_SUCCESS;

    return ret;
}

/********************************************************************
 ************************** Pre-activate ****************************
 ********************************************************************/

/**
 * @brief Pre-activate hook for plugin
 * @param[in] lzeh
 * @return @p LIBZE_ERROR_SUCCESS
 */
libze_error
libze_plugin_grub_pre_activate(libze_handle *lzeh) {
    return LIBZE_ERROR_SUCCESS;
}

/********************************************************************
 ************************** Mid-activate ****************************
 ********************************************************************/

/**
 * @brief Run mid-activate hook
 *
 * @param lzeh Initialized libze handle
 * @param activate_data New be to activate
 *
 * @return Non-zero on failure
 */
libze_error
libze_plugin_grub_mid_activate(libze_handle *lzeh, libze_activate_data *activate_data) {
    return LIBZE_ERROR_SUCCESS;
}

/********************************************************************
 ************************** Post-activate ****************************
 ********************************************************************/

/**
 * @brief Post-activate hook
 *
 * @param[in,out] lzeh  Initialized libze handle
 * @param[in] be_name   Boot environment to activate
 *
 * @return @p LIBZE_ERROR_SUCCESS on success,
 *         @p LIBZE_ERROR_UNKNOWN if update-grub fails
 */
libze_error
libze_plugin_grub_post_activate(libze_handle *lzeh, char const be_name[LIBZE_MAX_PATH_LEN]) {
    return update_grub();
}

/********************************************************************
 ************************** Post-create ****************************
 ********************************************************************/

/**
 * @brief Post-create hook
 *        Edits loader entry
 *        Copies kernels from BE being cloned
 *
 * @param[in,out] lzeh  libze handle
 * @param[in] create_data  BE being created
 *
 * @return @p LIBZE_ERROR_SUCCESS on success,
 *         @p LIBZE_ERROR_UNKNOWN if update-grub fails
 */
libze_error
libze_plugin_grub_post_create(libze_handle *lzeh, libze_create_data *create_data) {
    return update_grub();
}

/********************************************************************
 ************************** Post-destroy ****************************
 ********************************************************************/

/**
 * @brief Post-destroy hook
 *        Removes loader entry
 *        Deletes kernels from BE being destroyed
 *
 * @param[in,out] lzeh  libze handle
 * @param[in] be_name   BE being destroyed
 *
 * @return @p LIBZE_ERROR_SUCCESS on success,
 *         @p LIBZE_ERROR_MAXPATHLEN on buffer being exceeded,
 *         @p LIBZE_ERROR_UNKNOWN if update-grub fails
 */
libze_error
libze_plugin_grub_post_destroy(libze_handle *lzeh, char const be_name[LIBZE_MAX_PATH_LEN]) {
    return update_grub();
}

/********************************************************************
 ************************** Post-rename ****************************
 ********************************************************************/

/**
 * @brief Post-rename hook
 *        Renames loader entry
 *        Renames kernels directory
 *
 * @param[in,out] lzeh      libze handle
 * @param[in] be_name_old   Boot environment to be renamed
 * @param[in] be_name_new   New boot environment name
 *
 * @return     @p LIBZE_ERROR_MAXPATHLEN if path length exceeded
 *             @p LIBZE_ERROR_UNKNOWN if update-grub fails
 *             @p LIBZE_ERROR_SUCCESS on success
 */
libze_error
libze_plugin_grub_post_rename(libze_handle *lzeh, char const be_name_old[LIBZE_MAX_PATH_LEN],
                              char const be_name_new[LIBZE_MAX_PATH_LEN]) {
    return update_grub();
}

/**
 * @brief Pre snapshot hook
 *
 * @param[in,out] lzeh   libze handle
 * @param[in] snap_data  Snapshot related data
 * @return @p LIBZE_ERROR_SUCCESS on success
 */
libze_error
libze_plugin_grub_pre_snapshot(libze_handle *lzeh, libze_snap_data *snap_data) {
    return LIBZE_ERROR_SUCCESS;
}
