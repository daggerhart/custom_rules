# Custom Rules

Some simple examples of custom coditions and actions for the Drupal 7 Rules module: https://www.drupal.org/project/rules

### Conditions

* **Is Cron Running?** - Queries the semaphore table to determine cron status
* **Is During Password Reset?** - Checks route arguments for an expected path 
* **Is Destination Set?** - Checks for destination GET variable 
* **Is During OAuth?** - Checks for oauth2 route, or oauth2 in destination


### Actions

* **Delete field_collection_item** - Really delete field_collection_item. Needed because the normal Delete entity rule does not remove the hostEntity Reference.
* **Clear messages** - Search `$_SESSION['messages']` queue for a specific message to remove
