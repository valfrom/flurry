/*
java implementation of the s3eFlurry extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;
import com.flurry.android.*;

class s3eFlurry
{
    public void s3eFlurryStart(String ID)
    {
        FlurryAgent.onStartSession(LoaderAPI.getActivity(), ID);
    }
    public void s3eFlurryLogEvent(String eventName, boolean timed)
    {
		if(!timed)
			FlurryAgent.logEvent(eventName);
		else
			FlurryAgent.logEvent(eventName, timed);
    }
    public void s3eFlurryEndTimedEvent(String eventName)
    {
		FlurryAgent.endTimedEvent(eventName);
    }
    public void s3eFlurryLogError(String errorName, String errorMessage)
    {
		FlurryAgent.onError(errorName, errorMessage, "");
    }
    public void s3eFlurrySetUserID(String userID)
    {
        FlurryAgent.setUserId(userID);
    }
    public void s3eFlurrySetUserAge(int age)
    {
        FlurryAgent.setAge(age);
    }
    public void s3eFlurrySetUserGender(boolean isMale)
    {
		if(isMale)
			FlurryAgent.setGender(Constants.MALE);
		else
			FlurryAgent.setGender(Constants.FEMALE);
    }
    public void s3eFlurrySetLocation()
    {
    }
    public void s3eFlurrySetSessionReportOnClose()
    {
    }
    public void s3eFlurrySetSessionReportOnPause()
    {
    }
}
