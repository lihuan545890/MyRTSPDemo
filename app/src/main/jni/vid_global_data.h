#ifndef VID_GLOBAL_DATA
#define VID_GLOBAL_DATA

class CVidGlobalData
{
	public:
		CVidGlobalData()
		{

		}

		virtual ~CVidGlobalData(){}

		static CVidGlobalData * Instance()
		{
			static CVidGlobalData _stance;
			return &_stance;
		}		

		void * m_pVidCapture;
		
};

#endif
