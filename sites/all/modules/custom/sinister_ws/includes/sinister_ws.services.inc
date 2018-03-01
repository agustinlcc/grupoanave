<?php

/**
 * @file
 * Retrieve a sinister info from uid.
 */

/**
 * Return data from sinister.
 */
function sinister_ws_resource_retrieve($uid) {
  $sinisters = sinister_get_ajustador_sinisters($uid, 1);
  $objects = array();
  foreach ($sinisters as $nid => $sinister) {
    if (!($node = node_load($nid))) {
      continue;
    }
    // Get fields from poliza.
    $poliza_nid = $node->field_poliza[LANGUAGE_NONE][0]['target_id'];
    $poliza_fields = entity_load_single('node', $poliza_nid);
    // Get fields value from vehicle brand.
    $sub_brand_term = taxonomy_term_load($poliza_fields->field_vehiculo_submarca[LANGUAGE_NONE][0]['tid']);
    $sub_brand = $sub_brand_term->name;
    // Get vehicle model field value.
    $vehicle_model = $poliza_fields->field_vehiculo_modelo[LANGUAGE_NONE][0]['value'];
    // Get vehicle model field value.
    $vehicle_color = $poliza_fields->field_vehiculo_color[LANGUAGE_NONE][0]['value'];
    // Create return object.
    $return_obj = array(
      'id' => $node->nid,
      'sinister' => $node->title,
      'created' => date('Y/m/d H:s A', $node->created),
    );
    if (isset($sub_brand)) {
      $return_obj['tipo'] = $sub_brand;
    }
    if (isset($vehicle_color)) {
      $return_obj['color'] = $vehicle_color;
    }
    if (isset($vehicle_model)) {
      $return_obj['model'] = $vehicle_model;
    }
    $objects[$nid] = $return_obj;
  }
  return $objects;
}