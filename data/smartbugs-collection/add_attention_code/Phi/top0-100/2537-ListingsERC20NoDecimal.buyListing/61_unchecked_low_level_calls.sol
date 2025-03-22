 

 
 
 


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

  function mul(uint256 a, uint256 b) internal pure returns (uint256 c) {
    if (a == 0) {
      return 0;
    }
    c = a * b;
    assert(c / a == b);
    return c;
  }

  function div(uint256 a, uint256 b) internal pure returns (uint256) {
    return a / b;
  }

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
    c = a + b;
    assert(c >= a);
    return c;
  }
}

contract DetailedERC20 {
  function transferFrom(address from, address to, uint256 value) public returns (bool);
  function balanceOf(address who) public view returns (uint256);
  function allowance(address owner, address spender) public view returns (uint256);
}

contract ListingsERC20NoDecimal {
    using SafeMath for uint256;

    struct Listing {
        address seller;
        address tokenContractAddress;
        uint256 price;
        uint256 allowance;
        uint256 dateEnds;
    }

    mapping (bytes32 => Listing) public listings;
    mapping (bytes32 => uint256) public sold;
    uint256 public ownerPercentage;
    uint16 constant public GAS_LIMIT = 4999;

    event ListingBought(bytes32 indexed listingId, address tokenContractAddress, uint256 price, uint256 amount, uint256 dateBought, address buyer);

    function getBalance(address tokenContract, address seller) internal returns (uint256) {
        return DetailedERC20(tokenContract).balanceOf.gas(GAS_LIMIT)(seller);
    }

    function getAllowance(address tokenContract, address seller, address listingContract) internal returns (uint256) {
        return DetailedERC20(tokenContract).allowance.gas(GAS_LIMIT)(seller, listingContract);
    }

    function buyListing(bytes32 listingId, uint256 amount) external payable {
        Listing storage listing = listings[listingId];
        address seller = listing.seller;
        address contractAddress = listing.tokenContractAddress;
        uint256 price = listing.price;

        uint256 sale = price.mul(amount);
        uint256 allowance = listing.allowance;

        require(now <= listing.dateEnds);
        require(allowance - sold[listingId] >= amount);
        require(getBalance(contractAddress, seller) >= amount);
        require(getAllowance(contractAddress, seller, this) >= amount);
        require(msg.value == sale);

        DetailedERC20 tokenContract = DetailedERC20(contractAddress);
        require(tokenContract.transferFrom(seller, msg.sender, amount));

        if (ownerPercentage > 0) {
            seller.transfer(sale - (sale.mul(ownerPercentage).div(10000)));
        } else {
            seller.transfer(sale);
        }

        sold[listingId] = sold[listingId].add(amount);
        emit ListingBought(listingId, contractAddress, price, amount, now, msg.sender);
    }
}
