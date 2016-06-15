<?php

/**
 * Implements hook_rules_action_info().
 */
function custom_rules_rules_action_info() {
	return array(
		// use the field_collection_item entity to delete a field_collection_item correctly
		'custom_rules_delete_field_collection_item' => array(
			'label' => t('Delete field_collection_item and hostEntity reference (Custom Rules)'),
			'group' => t('Custom Rules'),
			'parameter' => array(
				'field_collection_item' => array(
					'type' => 'field_collection_item',
					'label' => t('Field collection item remove'),
					'description' => t('Field collection item and hostEntity reference will be deleted.'),
				),
			),
		),

		// set an node to private and immediately save it to ensure its privacy
		'custom_rules_drupal_get_messages' => array(
			'label' => t('Clear messages with drupal_get_messages() (Custom Rules)'),
			'group' => t('Custom Rules'),
			'parameter' => array(
				'type_to_remove' => array(
					'type' => 'text',
					'label' => t('Message type'),
					'description' => t('Provide a message type to be removed: ( status, error, warning, etc ). Use "any" for typeless removal. Use "all" for clearing all messages.'),
				),
				'message_to_remove' => array(
					'type' => 'text',
					'label' => t('Message to remove'),
					'description' => t('Provide the message string to be removed.'),
				),
			),
		),
	);
}

/**
 * Simple helper action to really delete field_collection_item
 * The normal Delete entity rule does not remove the hostEntity Reference
 *
 * @param $field_collection_item
 */
function custom_rules_delete_field_collection_item( $field_collection_item ){
	$field_collection_item->delete();
}

/**
 * Search $_SESSION[messages] queue for a specific message to remove
 *
 * @param $type_to_remove
 * @param $message_to_remove
 */
function custom_rules_drupal_get_messages( $type_to_remove, $message_to_remove ){
	$index = FALSE;
	$found_type = FALSE;

	// remove all messages
	if ( $type_to_remove == "all" ){
		drupal_get_messages();
	}
	// search all messages for the string
	else if ( $type_to_remove == "any" ) {
		$messages = drupal_get_messages( NULL, false );

		foreach ($messages as $message_type => $type_messages){
			$index = array_search( $message_to_remove, $type_messages );
			if ( $index !== FALSE ){
				$found_type = $message_type;
				break;
			}
		}
	}
	// look for messages of a specific type
	else {
		$messages = drupal_get_messages( $type_to_remove, false );
		if ( isset( $messages[ $type_to_remove ] ) ) {
			$index = array_search( $message_to_remove, $messages[ $type_to_remove ] );
		}

		if ( $index !== FALSE ) {
			$found_type = $type_to_remove;
		}
	}

	// if found, remove the message from $_SESSION[messages] queue
	if ( $index !== FALSE &&
	     $found_type !== FALSE &&
	     isset( $_SESSION['messages'][ $found_type ][ $index ] ) )
	{
		unset( $_SESSION['messages'][ $found_type ][ $index ] );

		// remove the entire type if now empty
		if ( empty( $_SESSION['messages'][ $found_type ] ) ){
			unset( $_SESSION['messages'][ $found_type ] );
		}
	}
}
