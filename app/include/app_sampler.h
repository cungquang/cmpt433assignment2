#ifndef _APP_SAMPLER_H_
#define _APP_SAMPLER_H_

//Thread
void Sampler_init(int *terminate_flag);

//Cleanup
void Sampler_cleanup();

// Getter
int Sampler_getHistorySize(void);
double Sampler_getAverageReading(void);
long long Sampler_getNumSamplesTaken(void); 
//double *Sampler_getHistory(int *size);

#endif