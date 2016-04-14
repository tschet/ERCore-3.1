<?php
class er_page{
	protected $content_type_info;
	protected $template_dir;
	protected $range;
	protected $date_format = 'M j, Y';
	
	protected static $field_aliases = array(
		'position_type'=>'field_er_most_sen_proj_role',
		'fname'=>'field_er_fname',
		'lname'=>'field_er_lname',
		'department'=>'field_er_department',
		'inst_abbr'=>'field_er_inst_abbreviation',
		'inst_ref'=>'field_er_inst_ref',
		'160hours'=>'field_er_160hours',
		'participating'=>'field_er_inst_participating',
		'committee'=>'field_er_committees',
		'gender'=>'field_er_gender',
		'race'=>'field_er_race',
		'ethnicity'=>'field_er_ethnicity',
		'disability'=>'field_er_disabilities',
		'participant_date'=>'field_er_participating_date',
		'hired_date'=>'field_er_hired_date',
		'leadership_team'=>'field_er_leadership_team',
		'mas_act_grad_date'=>'field_er_act_masters',
		'doc_act_grad_date'=>'field_er_act_doctor',
		'und_act_grad_date'=>'field_er_act_under',
		'collab_inst_ref' => 'field_er_collab_inst_ref',
		'collab_department_unit' => 'field_er_collab_department_unit',
		'inst_category' => 'field_er_inst_category',
		'inst_type' => 'field_er_inst_type',
		'collab_user_status' => 'field_er_collab_user_status',
		'collab_name' => 'field_er_collab_name',
		'collab_ref' => 'field_er_collab_ref',
		'collab_date' => 'field_er_collaboration_dates',
	);
	
	public function __construct() {
		$this->range = er_get_reporting_range();
		//$this->template_dir = drupal_get_path('module', 'er') . '/templates/';
	}
	
	/*
	 * These are the primary methods that you can overload in child classes.
	 */
	
	public function title(){
		return "Reporting".$this->range_string();
	}
	
	public function range_string(){
		return ' ['.date($this->date_format, $this->range[0]).' - '.date($this->date_format, $this->range[1]).']';
	}
	
	public function data(){
		return array();
	}
	
	public function html(){
		$data = $this->data();
		d($data);
		return "";
	}
	
	/*
	 * This function returns a PHPExcel object. 
	 * See: PHPExcel library
	 */
	public function excel(){
		$objPHPExcel = $this->excel_file();
		$this->write_excel($objPHPExcel);
		$objPHPExcel->setActiveSheetIndex(0);
		return $objPHPExcel;
	}
	
	/*
	 * This function writes the data into an excel object.
	 */
	public function write_excel(&$objPHPExcel, $sheet = 0){
		$data = $this->data();
		$worksheet = $objPHPExcel->setActiveSheetIndex($sheet);
	}
	
	/*
	 * This function returns a PHPExcel object. 
	 * See: PHPExcel library
	 */
	public function excel_file(){
		//$objPHPExcel = PHPExcel_IOFactory::load($this->template_dir."Report-template.xls");
		
		//reference: http://stackoverflow.com/questions/3269345/how-to-generate-an-excel-document-with-multiple-worksheets-from-php
		$objPHPExcel = new PHPExcel();
		return $objPHPExcel;
	}

	/*
	 * HELPER METHODS:
	 */
	
	/*
	 * takes a column number (zero-based) and converts it into a string of letters
	 * to be used in setting values in excel sheets.
	 * ex:	0 -> A
	 * 		1 -> B
	 * ...	26 -> AA
	 * 		27 -> AB
	 */ 
	public function itol($num){
		$ret = '';
		for(;;){
			$ret = chr(ord('A')+($num%26)) . $ret;
			if ($num>=26)
				$num = $num/26 - 1;
			else
				break;
		}
		return $ret;
	}
	
	protected function download_link($title = "", $arg = "", $options = array()){
		return er_create_download_link($title, $arg, $options);
	}
	
	/*
	 * Gets allowed values for a cck field provided the name of the field.
	 * See: .../reporting/debug
	 */
	protected function get_allowed_values($field){
		$all_fields = field_info_fields();
		return list_allowed_values($all_fields[$field]);
	}

}
