<?php
/**
 * @file
 * js_snippet_injector/js_snippet_injector_form.inc
 * Admin Form
 */

/**
 * Implements hook_form().
 */
function js_snippet_injector_form($form, &$form_state) {
  $form = array();

  $form['#tree'] = TRUE;

  $form['code_snippets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Code Snippets'),
    '#prefix' => '<div id="code-snippets-fieldset-wrapper">',
    '#suffix' => '</div>',
  );

  if (empty($form_state['js_snippet_injector_num_fields']) && variable_get('js_snippet_injector_num_fields') != 1) {
    $form_state['js_snippet_injector_num_fields'] = variable_get('js_snippet_injector_num_fields');
  }

  for ($i = 0; $i < $form_state['js_snippet_injector_num_fields']; $i++) {

    // Count to display on form
    $display_num = $i + 1;

    $form['code_snippets']['code_snippets_' . $i] = array(
      '#type' => 'fieldset',
      '#title' => t('Code Snippets Item'),
    );

    $form['code_snippets']['code_snippets_' . $i]['js_snippet_injector_header_snippet_' . $i][$i] = array(
      '#type' => 'textarea',
      '#title' => t('Header Snippet Item @display_num',
                    array(
                      '@display_num' => check_plain($display_num)
                    )
                  ),
      '#default_value' => variable_get('js_snippet_injector_header_snippet_' . $i, ''),
      '#size' => 64,
      '#maxlength' => 128,
      '#description' => t("The code snippet to place in the header"),
      '#required' => FALSE,
    );

    $form['code_snippets']['code_snippets_' . $i]['js_snippet_injector_header_snippet_jquery_toggle_' . $i][$i] = array(
      '#type' => 'checkbox',
      '#title' => t('Use jQuery for Header Snippet Item  @display_num?',
                    array(
                      '@display_num' => check_plain($display_num)
                    )
                  ),
      '#default_value' => variable_get('js_snippet_injector_header_snippet_jquery_toggle_' . $i, ''),
      '#size' => 64,
      '#maxlength' => 128,
      '#description' => t("Wraps the item in document ready."),
      '#required' => FALSE,
    );

    $form['code_snippets']['code_snippets_' . $i]['js_snippet_injector_footer_snippet_' . $i][$i] = array(
      '#type' => 'textarea',
      '#title' => t('Footer Snippet Item  @display_num',
                    array(
                      '@display_num' => check_plain($display_num)
                    )
                  ),
      '#default_value' => variable_get('js_snippet_injector_footer_snippet_' . $i, ''),
      '#size' => 64,
      '#maxlength' => 128,
      '#description' => t("The code snippet to place in the footer"),
      '#required' => FALSE,
    );

    $form['code_snippets']['code_snippets_' . $i]['js_snippet_injector_footer_snippet_jquery_toggle_' . $i][$i] = array(
      '#type' => 'checkbox',
      '#title' => t('Use jQuery for Footer Snippet Item  @display_num?',
                    array(
                      '@display_num' => check_plain($display_num)
                    )
                  ),
      '#default_value' => variable_get('js_snippet_injector_footer_snippet_jquery_toggle_' . $i, ''),
      '#size' => 64,
      '#maxlength' => 128,
      '#description' => t("Wraps the item in document ready."),
      '#required' => FALSE,
    );

  }

  $form['code_snippets']['add_name'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#submit' => array('js_snippet_injector_form_add_one'),
    '#ajax' => array(
      'callback' => 'js_snippet_injector_form_callback',
      'wrapper' => 'code-snippets-fieldset-wrapper',
    ),
  );

  if ($form_state['js_snippet_injector_num_fields'] > 1) {
    $form['code_snippets']['remove_name'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('js_snippet_injector_form_remove_one'),
      '#ajax' => array(
        'callback' => 'js_snippet_injector_form_callback',
        'wrapper' => 'code-snippets-fieldset-wrapper',
      ),
    );
  }

  $form['js_snippet_injector_num_fields'] = array(
    '#type' => 'hidden',
    '#value' => variable_get('js_snippet_injector_num_fields', $form_state['js_snippet_injector_num_fields'])
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add Javascript'),
  );

  return $form;
}

/**
 * Implements hook_form_add_one().
 */
function js_snippet_injector_form_add_one($form, &$form_state) {
  $form_state['js_snippet_injector_num_fields']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_form_callback().
 */
function js_snippet_injector_form_callback($form, $form_state) {
  return $form['code_snippets'];
}

/**
 * Implements hook_form_remove_one().
 */
function js_snippet_injector_form_remove_one($form, &$form_state) {
  if ($form_state['js_snippet_injector_num_fields'] > 1) {
    $form_state['js_snippet_injector_num_fields']--;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_form_submit().
 */
function js_snippet_injector_form_submit($form, &$form_state) {
  variable_set('js_snippet_injector_num_fields', $form_state['js_snippet_injector_num_fields']);

  for ($i = 0; $i < $form_state['js_snippet_injector_num_fields']; $i++) {

    if (isset($form_state['values']['code_snippets']['code_snippets_' . $i]['js_snippet_injector_header_snippet_' . $i][$i])) {
      variable_set('js_snippet_injector_header_snippet_' . $i, $form_state['values']['code_snippets']['code_snippets_' . $i]['js_snippet_injector_header_snippet_' . $i][$i]);
    }

    if (isset($form_state['values']['code_snippets']['code_snippets_' . $i]['js_snippet_injector_header_snippet_jquery_toggle_' . $i][$i])) {
      variable_set('js_snippet_injector_header_snippet_jquery_toggle_' . $i, $form_state['values']['code_snippets']['code_snippets_' . $i]['js_snippet_injector_header_snippet_jquery_toggle_' . $i][$i]);
    }

    if (isset($form_state['values']['code_snippets']['code_snippets_' . $i]['js_snippet_injector_footer_snippet_' . $i][$i])) {
      variable_set('js_snippet_injector_footer_snippet_' . $i, $form_state['values']['code_snippets']['code_snippets_' . $i]['js_snippet_injector_footer_snippet_' . $i][$i]);
    }

    if (isset($form_state['values']['code_snippets']['code_snippets_' . $i]['js_snippet_injector_footer_snippet_jquery_toggle_' . $i][$i])) {
      variable_set('js_snippet_injector_footer_snippet_jquery_toggle_' . $i, $form_state['values']['code_snippets']['code_snippets_' . $i]['js_snippet_injector_footer_snippet_jquery_toggle_' . $i][$i]);
    }
  }

  drupal_set_message(t('Form submitted!'));
}