<?php

/**
 * Implements hook_rules_condition_info().
 *
 * http://www.drupalcontrib.org/api/drupal/contributions!rules!rules.api.php/function/hook_rules_condition_info/7
 */
function custom_rules_rules_condition_info() {
	return array(
		'custom_rules_is_cron_running' => array(
			'label' => t('Is cron running'),
			'group' => t('Custom Rules'),
		),
		'custom_rules_is_during_password_reset' => array(
			'label' => t('Is during password reset'),
			'group' => t('Custom Rules'),
		),
		'custom_rules_is_destination_set' => array(
			'label' => t('Is destination set in URL'),
			'group' => t('Custom Rules'),
		),
		'custom_rules_is_during_oauth' => array(
			'label' => t('Is during OAuth'),
			'group' => t('Custom Rules'),
		),
	);
}

/**
 * Condition - is cron running?
 *
 * @return bool
 */
function custom_rules_is_cron_running(){
	$cron_expires = db_query("SELECT `expire` FROM {semaphore} WHERE `name` = 'cron' LIMIT 1")->fetchField();

	if ( $cron_expires && $cron_expires > microtime(TRUE) ) {
		return TRUE;
	}

	return FALSE;
}

/**
 * Condition - is a user password currently being reset?
 *
 * @return bool
 */
function custom_rules_is_during_password_reset(){
	return (arg(0) == 'user' && arg(1) == 'reset');
}

/**
 * Condition - destination set in url query
 *
 * @return bool
 */
function custom_rules_is_destination_set(){
	return isset( $_GET['destination'] );
}

/**
 * Condition - Check if user is being processed through oauth
 *
 * @return bool
 */
function custom_rules_is_during_oauth(){
	return (
		// on oauth route itself
		arg(0) == 'oauth2' ||
		// or logging in using the form
		( isset( $_GET['destination'] ) &&
		  stripos( $_GET['destination'], 'oauth2' ) !== FALSE )
	);
}
