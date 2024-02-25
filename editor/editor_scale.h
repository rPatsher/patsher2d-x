#ifndef EDITOR_SCALE_H
#define EDITOR_SCALE_H




class EditorScale {
	static float _scale;

public:
	static void set_scale(float p_scale);
	static float get_scale();

#define ESCALE (EditorScale::get_scale())
	


};




#endif // EDITOR_SCALE_H