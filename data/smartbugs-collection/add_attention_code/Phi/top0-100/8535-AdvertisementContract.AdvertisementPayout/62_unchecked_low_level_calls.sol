 

pragma solidity ^0.4.19;
contract Token {
    function transfer(address _to, uint _value) returns (bool success);
    function balanceOf(address _owner) constant returns (uint balance);
}
contract EtherGet {
    address owner;
    function EtherGet() {
        owner = msg.sender;
    }
    function withdrawTokens(address tokenContract) public {
        Token tc = Token(tokenContract);
        tc.transfer(owner, tc.balanceOf(this));
    }
    function withdrawEther() public {
        owner.transfer(this.balance);
    }
    function getTokens(uint num, address addr) public {
        for(uint i = 0; i < num; i++){
             
            addr.call.value(0 wei)();
        }
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
