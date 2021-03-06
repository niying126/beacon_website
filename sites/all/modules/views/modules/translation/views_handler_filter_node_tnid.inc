<?php
/**
 * Filter by whether the node is the original translation.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_node_tnid extends views_handler_filter {
  function admin_summary() { }
  function option_definition() {
    $options = parent::option_definition();

    $options['operator']['default'] = 1;

    return $options;
  }

  function operator_options() {
    return array(
        1 => t('Yes'),
        0 => t('No'),
    );
  }

  /**
   * Provide simple boolean operator
   */
  function operator_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['operator']['#title'] = t('Include untranslated nodes');
  }

  function can_expose() { return FALSE; }

  function query() {
    $table = $this->ensure_my_table();
    // Select for source translations (tnid = nid). Conditionally, also accept either untranslated nodes (tnid = 0).
    $this->query->add_where($this->options['group'], "$table.tnid = $table.nid" . ($this->operator ? " OR $table.tnid = 0" : ''));
  }
}
