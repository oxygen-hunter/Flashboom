 

pragma solidity ^0.4.21;

contract GuessTheRandomNumberChallenge {
    uint8 answer;

    function GuessTheRandomNumberChallenge() public payable {
        require(msg.value == 1 ether);
         
        answer = uint8(keccak256(block.blockhash(block.number - 1), now));
    }

    function isComplete() public view returns (bool) {
        return address(this).balance == 0;
    }

    function guess(uint8 n) public payable {
        require(msg.value == 1 ether);

        if (n == answer) {
            msg.sender.transfer(2 ether);
        }
    }
}

contract SafeMath {
    function safeAdd(uint a, uint b) pure internal returns (uint) {
        uint c = a + b;
        sAssert(c>=a && c>=b);
        return c;
    }

    function sAssert(bool assertion) pure internal {
        if (!assertion) {
            revert();
        }
    }
}

contract SingleSourceIdentity is SafeMath {
    event IdentityApproval(address indexed authority, address indexed walletAddress, uint verifiedAttributes);

    struct KYC {
        bool verified;
        address verifiedBy;
        uint verifiedAt;
        uint verifiedAttributes;
    }

    uint public verificationFee;
    mapping(address => uint) public verificationFeeBalances;
    address public paymentContractAddress;
    mapping(address => KYC) public records;

    modifier onlyValidAuthority(address authorityAddress) {
        if (!isValidAuthority(authorityAddress)) {
            revert();
        }
        _;
    }

    modifier onlyAuthoritativeAuthority(address authorityAddress, address userAddress) {
        KYC storage kycRecord = records[userAddress];
        if (kycRecord.verifiedBy != 0x0 && kycRecord.verifiedBy != authorityAddress) {
            if (isValidAuthority(kycRecord.verifiedBy)) {
                revert();
            }
        }
        _;
    }

    function isValidAuthority(address authorityAddress)
      private
      view
      returns (bool)
    {
        Authority authority = Authority(authorityContractAddress);
        return authority.isValidAuthority(authorityAddress, block.number);
    }

    function chargeVerificationFee(address userAddress, address authorityAddress)
      private
      returns (bool)
    {
        if (!ERC20(paymentContractAddress).transferFrom(userAddress, this, verificationFee)) {
            return false;
        }
        uint currentBalance = verificationFeeBalances[authorityAddress];
        verificationFeeBalances[authorityAddress] = safeAdd(currentBalance, verificationFee);
        return true;
    }

    function claim(address verifier, uint verifiedAttributes, uint expires, uint8 v, bytes32 r, bytes32 s)
      public
      onlyValidAuthority(verifier)
      onlyAuthoritativeAuthority(verifier, msg.sender)
    {
        if (verificationFee > 0) {
            if(!chargeVerificationFee(msg.sender, verifier)) {
                revert();
            }
        }

        bytes32 hash = sha256(this, msg.sender, verifiedAttributes, expires);
        bytes memory prefix = "\x19Ethereum Signed Message:\n32";
        bytes32 prefixedHash = keccak256(prefix, hash);

        if (!((ecrecover(prefixedHash, v, r, s) == verifier) && block.number <= expires)) {
            revert();
        }

        KYC memory kyc = KYC({
            verified: true,
            verifiedBy: verifier,
            verifiedAt: block.number,
            verifiedAttributes: verifiedAttributes
        });

        records[msg.sender] = kyc;

        emit IdentityApproval(verifier, msg.sender, verifiedAttributes);
    }
}
