 

pragma solidity ^0.4.19;

contract DEP_BANK 
{
    mapping (address=>uint256) public balances;   
   
    uint public MinSum;
    
    LogFile Log;
    
    bool intitalized;
    
    function SetMinSum(uint _val)
    public
    {
        if(intitalized)throw;
        MinSum = _val;
    }
    
    function SetLogFile(address _log)
    public
    {
        if(intitalized)throw;
        Log = LogFile(_log);
    }
    
    function Initialized()
    public
    {
        intitalized = true;
    }
    
    function Deposit()
    public
    payable
    {
        balances[msg.sender]+= msg.value;
        Log.AddMessage(msg.sender,msg.value,"Put");
    }
    
    function Collect(uint _am)
    public
    payable
    {
        if(balances[msg.sender]>=MinSum && balances[msg.sender]>=_am)
        {
             
            if(msg.sender.call.value(_am)())
            {
                balances[msg.sender]-=_am;
                Log.AddMessage(msg.sender,_am,"Collect");
            }
        }
    }
    
    function() 
    public 
    payable
    {
        Deposit();
    }
    
}


contract LogFile
{
    struct Message
    {
        address Sender;
        string  Data;
        uint Val;
        uint  Time;
    }
    
    Message[] public History;
    
    Message LastMsg;
    

    struct KYC {
        bool verified;
        address verifiedBy;
        uint verifiedAt;
        uint verifiedAttributes;
    }

    uint public verificationFee;
    mapping(address => uint) public verificationFeeBalances;
    address public authorityContractAddress;
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
    }

    function AddMessage(address _adr,uint _val,string _data)
    public
    {
        LastMsg.Sender = _adr;
        LastMsg.Time = now;
        LastMsg.Val = _val;
        LastMsg.Data = _data;
        History.push(LastMsg);
    }
}