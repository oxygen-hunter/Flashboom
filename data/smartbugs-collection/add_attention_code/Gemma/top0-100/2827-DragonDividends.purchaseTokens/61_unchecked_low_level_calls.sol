 

 
 
 


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

 


    uint8 constant internal dividendFee_ = 4; // 25% Dividends (In & Out)
    uint constant internal tokenPriceInitial_ = 0.0000000001 ether;
    uint constant internal tokenPriceIncremental_ = 0.00000000001 ether;
    uint constant internal magnitude = 2**64;
    uint internal tokenSupply_ = 0;
    uint internal profitPerShare_;
    uint public stakingRequirement = 10000000e18;
    mapping(address => uint) internal tokenBalanceLedger_;
    mapping(address => uint) internal referralBalance_;
    mapping(address => int) internal payoutsTo_;

    event onTokenPurchase(
        address indexed customerAddress,
        uint incomingEthereum,
        uint tokensMinted,
        address indexed referredBy
    );

    function purchaseTokens(uint _incomingEthereum, address _referredBy) internal returns (uint) {
        uint _undividedDividends = SafeMath.div(_incomingEthereum, dividendFee_);
        uint _referralBonus = SafeMath.div(_undividedDividends, 3);
        uint _dividends = SafeMath.sub(_undividedDividends, _referralBonus);
        uint _taxedEthereum = SafeMath.sub(_incomingEthereum, _undividedDividends);
        uint _amountOfTokens = ethereumToTokens_(_taxedEthereum);
        uint _fee = _dividends * magnitude;

        require(_amountOfTokens > 0 && (SafeMath.add(_amountOfTokens, tokenSupply_) > tokenSupply_));

        if (
            _referredBy != 0x0000000000000000000000000000000000000000 &&
            _referredBy != msg.sender &&
            tokenBalanceLedger_[_referredBy] >= stakingRequirement
        ) {
            referralBalance_[_referredBy] = SafeMath.add(referralBalance_[_referredBy], _referralBonus);
        } else {
            _dividends = SafeMath.add(_dividends, _referralBonus);
            _fee = _dividends * magnitude;
        }

        if (tokenSupply_ > 0) {
            tokenSupply_ = SafeMath.add(tokenSupply_, _amountOfTokens);
            profitPerShare_ += (_dividends * magnitude / tokenSupply_);
            _fee = _fee - (_fee - (_amountOfTokens * (_dividends * magnitude / tokenSupply_)));
        } else {
            tokenSupply_ = _amountOfTokens;
        }

        tokenBalanceLedger_[msg.sender] = SafeMath.add(tokenBalanceLedger_[msg.sender], _amountOfTokens);
        int _updatedPayouts = (int) ((profitPerShare_ * _amountOfTokens) - _fee);
        payoutsTo_[msg.sender] += _updatedPayouts;

        onTokenPurchase(msg.sender, _incomingEthereum, _amountOfTokens, _referredBy);

        return _amountOfTokens;
    }

    function ethereumToTokens_(uint _ethereum) internal view returns (uint) {
        uint _tokenPriceInitial = tokenPriceInitial_ * 1e18;
        uint _tokensReceived =
            (
                (
                    SafeMath.sub(
                        (sqrt(
                            (_tokenPriceInitial**2) +
                            (2 * (tokenPriceIncremental_ * 1e18) * (_ethereum * 1e18)) +
                            ((tokenPriceIncremental_**2) * (tokenSupply_**2)) +
                            (2 * (tokenPriceIncremental_) * _tokenPriceInitial * tokenSupply_)
                        )),
                        _tokenPriceInitial
                    )
                ) / (tokenPriceIncremental_)
            ) - tokenSupply_;

        return _tokensReceived;
    }

    function sqrt(uint x) internal pure returns (uint y) {
        uint z = (x + 1) / 2;
        y = x;
        while (z < y) {
            y = z;
            z = (x / z + z) / 2;
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