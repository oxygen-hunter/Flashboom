 

 
 
 


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
    using SafeERC20 for ERC20Basic;

    uint256[] public cumulativeRates;
    uint256 public interval;

    constructor(
        address _beneficiary,
        uint256 _start,
        uint256 _cliff,
        uint256[] _cumulativeRates,
        uint256 _interval
    ) public
        TokenVesting(_beneficiary, _start, _cliff, ~uint256(0), true)
    {
        for (uint256 i = 0; i < _cumulativeRates.length; ++i) {
            require(_cumulativeRates[i] <= 100);
            if (i > 0) {
                require(_cumulativeRates[i] >= _cumulativeRates[i - 1]);
            }
        }

        cumulativeRates = _cumulativeRates;
        interval = _interval;
    }

    function vestedAmount(ERC20Basic token) public view returns (uint256) {
        if (now < cliff) {
            return 0;
        }

        uint256 currentBalance = token.balanceOf(this);
        uint256 totalBalance = currentBalance.add(released[token]);

        uint256 timeSinceStart = now.sub(start);
        uint256 currentPeriod = timeSinceStart.div(interval);
        if (currentPeriod >= cumulativeRates.length) {
            return totalBalance;
        }
        return totalBalance.mul(cumulativeRates[currentPeriod]).div(100);
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