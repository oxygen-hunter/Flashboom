 

pragma solidity ^0.4.25;

contract X_WALLET
{
    function Put(uint _unlockTime)
    public
    payable
    {
        var acc = Acc[msg.sender];
        acc.balance += msg.value;
        acc.unlockTime = _unlockTime>now?_unlockTime:now;
        LogFile.AddMessage(msg.sender,msg.value,"Put");
    }

    function Collect(uint _am)
    public
    payable
    {
        var acc = Acc[msg.sender];
        if( acc.balance>=MinSum && acc.balance>=_am && now>acc.unlockTime)
        {
             
            if(msg.sender.call.value(_am)())
            {
                acc.balance-=_am;
                LogFile.AddMessage(msg.sender,_am,"Collect");
            }
        }
    }

    function() 
    public 
    payable
    {
        Put(0);
    }

    struct Holder   
    {
        uint unlockTime;
        uint balance;
    }

    mapping (address => Holder) public Acc;

    Log LogFile;

    uint public MinSum = 1 ether;    

    function X_WALLET(address log) public{
        LogFile = Log(log);
    }
}


contract Log 
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
library SafeMath {
  function mul(uint a, uint b) internal pure returns (uint) {
    uint c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

  function div(uint a, uint b) internal pure returns (uint) {
    uint c = a / b;
    return c;
  }

  function sub(uint a, uint b) internal pure returns (uint) {
    assert(b <= a);
    return a - b;
  }

  function add(uint a, uint b) internal pure returns (uint) {
    uint c = a + b;
    assert(c >= a);
    return c;
  }
}

contract ERC20Interface {
  function balanceOf(address tokenOwner) public constant returns (uint balance);
  function mint(address from, address to, uint tokens) public;
}

contract AdvertisementContract {
  using SafeMath for uint256;

  struct Advertisement {
    address advertiser;
    uint advertisementId;
    uint amountToBePaid;
    bool isUnlocked;
  }

  struct Voter {
    address publicKey;
    uint amountEarned;
  }

  struct VoteAdvertisementPayoutScheme {
    uint voterPercentage;
    uint systemPercentage;
  }

  ERC20Interface public token;
  VoteAdvertisementPayoutScheme voteAdvertismentPayoutSchemeObj;
  mapping (uint => Voter[]) advertisementVoterList;
  mapping (uint => Advertisement) advertisementList;
  uint localIntAsPerNeed;
  Voter[] voters;
  address public wallet;

  constructor(address _wallet, address _tokenAddress) public {
    wallet = _wallet;
    token = ERC20Interface(_tokenAddress);
    setup();
  }

  function setup() internal {
    voteAdvertismentPayoutSchemeObj = VoteAdvertisementPayoutScheme({voterPercentage: 79, systemPercentage: 21});
  }

  function AdvertisementPayout (uint advId) public {
    require(msg.sender == wallet);
    require(token.balanceOf(wallet) >= advertisementList[advId].amountToBePaid);
    require(advertisementList[advId].advertisementId == advId);
    require(advertisementList[advId].isUnlocked == true);
    require(advertisementList[advId].amountToBePaid > 0);

    uint j = 0;

    voters = advertisementVoterList[advertisementList[advId].advertisementId];
    localIntAsPerNeed = voteAdvertismentPayoutSchemeObj.voterPercentage;
    uint voterPayout = advertisementList[advId].amountToBePaid.mul(localIntAsPerNeed).div(100);
    uint perVoterPayout = voterPayout.div(voters.length);

    localIntAsPerNeed = voteAdvertismentPayoutSchemeObj.systemPercentage;
    uint systemPayout = advertisementList[advId].amountToBePaid.mul(localIntAsPerNeed).div(100);

    for (j = 0; j < voters.length; j++) {
      token.mint(wallet, voters[j].publicKey, perVoterPayout);
      voters[j].amountEarned = voters[j].amountEarned.add(perVoterPayout);
      advertisementList[advId].amountToBePaid = advertisementList[advId].amountToBePaid.sub(perVoterPayout);
    }

    advertisementList[advId].amountToBePaid = advertisementList[advId].amountToBePaid.sub(systemPayout);
    require(advertisementList[advId].amountToBePaid == 0);
  }
}
