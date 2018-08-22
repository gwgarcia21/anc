
class AdaptiveFxFIRResults
{
public:
	/*float32_t * x = nullptr;
	float32_t * fx = nullptr;
	float32_t * d = nullptr;
	float32_t * y = nullptr;
	float32_t * e = nullptr;
	float32_t * mse = nullptr;
	float32_t * w = nullptr;*/
	float32_t ax[128] = { 0 };
	float32_t afx[128] = { 0 };
	float32_t ad[128] = { 0 };
	float32_t ay[128] = { 0 };
	float32_t ae[128] = { 0 };
	float32_t aw[256] = { 0 };
	float32_t * x = ax;
	float32_t * fx = afx;
	float32_t * d = ad;
	float32_t * y = ay;
	float32_t * e = ae;
	float32_t * w = aw;
	/* Static access method. */
	static AdaptiveFxFIRResults* getInstance(){
		if(!instance) {
			instance = new AdaptiveFxFIRResults();
		}

		return instance;
	}
private:
	/* Here will be the instance stored. */
	static AdaptiveFxFIRResults* instance;

	/* Private constructor to prevent instancing. */
	AdaptiveFxFIRResults(){};
};
