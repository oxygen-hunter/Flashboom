 

 
 
 


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

 



  using SafeMath for uint256;

  EVOAIToken public token;
  uint256 public rate;
  uint256 public weiRaisedRound;
  bool public privateStage;
  bool public preICOStage;
  bool public icoRound1;
  bool public icoRound2;
  bool public icoRound3;
  bool public icoRound4;
  bool public icoRound5;
  bool public icoRound6;

  constructor(address _wallet, address _walletForETH) public {
    require(_wallet != address(0));
    require(_walletForETH != address(0));

    token = new EVOAIToken();
    token.transfer(_wallet, 3200000000000000000000000);
    privateStage = true;
  }

  function _preValidatePurchase(address _beneficiary, uint256 _weiAmount) internal {
    require(_beneficiary != address(0));
    require(_weiAmount != 0);

    if (privateStage && weiRaisedRound.add(_weiAmount) <= 276000000000000000000) {
      rate = 1087;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (preICOStage && weiRaisedRound.add(_weiAmount) <= 775000000000000000000) {
      rate = 870;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    }  
    else if (icoRound1 && weiRaisedRound.add(_weiAmount) <= 1380000000000000000000) {
      rate = 725;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    }  
    else if (icoRound2 && weiRaisedRound.add(_weiAmount) <= 1610000000000000000000) {
      rate = 621;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound3 && weiRaisedRound.add(_weiAmount) <= 1840000000000000000000) {
      rate = 544;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound4 && weiRaisedRound.add(_weiAmount) <= 2070000000000000000000) {
      rate = 484;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound5 && weiRaisedRound.add(_weiAmount) <= 2300000000000000000000) {
      rate = 435;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    } 
    else if (icoRound6 && weiRaisedRound.add(_weiAmount) <= 2530000000000000000000) {
      rate = 396;
      weiRaisedRound = weiRaisedRound.add(_weiAmount);
    }
  }
  

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