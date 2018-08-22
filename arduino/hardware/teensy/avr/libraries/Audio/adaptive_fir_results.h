
class AdaptiveFIRResults
{
public:
	/*float32_t * x = nullptr;
	float32_t * d = nullptr;
	float32_t * y = nullptr;
	float32_t * e = nullptr;
	float32_t * mse = nullptr;
	float32_t * w = nullptr;*/
	
	float32_t ax[128] = { 0 };
	float32_t ad[128] = { 0 };
	float32_t ay[128] = { 0 };
	float32_t ae[128] = { 0 };
	float32_t aw[256] = { 0 };
	float32_t * x = ax;
	float32_t * d = ad;
	float32_t * y = ay;
	float32_t * e = ae;
	float32_t * w = aw;
	/* Static access method. */
	static AdaptiveFIRResults* getInstance(){
		if(!instance) {
			instance = new AdaptiveFIRResults();
		}

		return instance;
	}
private:
	/* Here will be the instance stored. */
	static AdaptiveFIRResults* instance;

	/* Private constructor to prevent instancing. */
	AdaptiveFIRResults(){};
};
