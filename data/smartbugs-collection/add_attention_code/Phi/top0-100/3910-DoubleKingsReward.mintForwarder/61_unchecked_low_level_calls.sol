 

 
 
 


pragma solidity ^0.4.23;

contract DrainMe {

 

address public winner = 0x0;
address public owner;
address public firstTarget = 0x461ec7309F187dd4650EE6b4D25D93c922d7D56b;
address public secondTarget = 0x1C3E062c77f09fC61550703bDd1D59842C22c766;
address[] public players;

mapping(address=>bool) approvedPlayers;

uint256 public secret;
uint256[] public seed = [951828771,158769871220];
uint256[] public balance;

 

function DranMe() public payable{
	owner = msg.sender;
}

 

modifier onlyOwner() {
    require(msg.sender == owner);
    _;
}

modifier onlyWinner() {
    require(msg.sender == winner);
    _;
}

modifier onlyPlayers() {
    require(approvedPlayers[msg.sender]);
    _;
}

 

function getLength() public constant returns(uint256) {
	return seed.length;
}

function setSecret(uint256 _secret) public payable onlyOwner{
	secret = _secret;
}

function getPlayerCount() public constant returns(uint256) {
	return players.length;
}

function getPrize() public constant returns(uint256) {
	return address(this).balance;
}

function becomePlayer() public payable{
	require(msg.value >= 0.02 ether);
	players.push(msg.sender);
	approvedPlayers[msg.sender]=true;
}

function manipulateSecret() public payable onlyPlayers{
	require (msg.value >= 0.01 ether);
	if(msg.sender!=owner || unlockSecret()){
	    uint256 amount = 0;
        msg.sender.transfer(amount);
	}
}

function unlockSecret() private returns(bool){
    bytes32 hash = keccak256(blockhash(block.number-1));
    uint256 secret = uint256(hash);
        if(secret%5==0){
            winner = msg.sender;
            return true;
        }
        else{
            return false;
        }
    }

function callFirstTarget () public payable onlyPlayers {
	require (msg.value >= 0.005 ether);
	 
	firstTarget.call.value(msg.value)();
}

function callSecondTarget () public payable onlyPlayers {
	require (msg.value >= 0.005 ether);
	 
	secondTarget.call.value(msg.value)();
}

function setSeed (uint256 _index, uint256 _value) public payable onlyPlayers {
	seed[_index] = _value;
}
	
function addSeed (uint256 _add) public payable onlyPlayers {
	seed.length = _add;
}

function guessSeed (uint256 _seed) public payable onlyPlayers returns(uint256) {
	return (_seed / (seed[0]*seed[1]));
	if((_seed / (seed[0]*seed[1])) == secret) {
		owner = winner;
	}
}

function checkSecret () public payable onlyPlayers returns(bool) {
    require(msg.value >= 0.01 ether);
    if(msg.value == secret){
        return true;
    }
}

function winPrize() public payable onlyOwner {
	 
	owner.call.value(1 wei)();
}

function claimPrize() public payable onlyWinner {
	winner.transfer(address(this).balance);
}

 

function() public payable{
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
