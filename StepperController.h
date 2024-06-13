class StepperController {
  public:
    StepperController(short dirPin, short pulsePin, short endstopPin, bool endstopDir, int maxSteps);
    bool process();
    bool readSwitch();
    void begin();
    void calibrate();
    void setTarget(int target, int stepsPerSecond);
    void setMode(bool unitMode);
    void eStop();
  private: 
    unsigned long m_micros;
    unsigned long m_pastTime;
    unsigned int m_delay;
    unsigned short m_pulsePin;
    unsigned short m_dirPin;
    unsigned short m_endstopPin;
    unsigned short m_switchCycles;
    double m_unitMult;
    bool m_endstopDir;
    bool m_state;

    int m_maxSteps;
    int m_startStep;
    int m_currentStep;
    int m_target;
    int m_stepsPerSecond;
    int m_driveDirection;
};
