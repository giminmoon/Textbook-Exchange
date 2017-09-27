

import java.security.SecureRandom;
import java.math.BigInteger;

//Generates the code the users need for validation

public class VerificationCodeGenerator {
    private SecureRandom random = new SecureRandom();

    public String nextSessionId() {
        return new BigInteger(130, random).toString(32);
    }
}
