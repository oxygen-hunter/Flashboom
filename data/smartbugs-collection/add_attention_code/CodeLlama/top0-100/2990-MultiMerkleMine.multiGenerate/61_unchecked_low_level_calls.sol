 

 
 
 


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
contract MultiMerkleMine {
	using SafeMath for uint256;

	function multiGenerate(address _merkleMineContract, address[] _recipients, bytes _merkleProofs) public {
		MerkleMine mine = MerkleMine(_merkleMineContract);
		ERC20 token = ERC20(mine.token());

		require(
			block.number >= mine.callerAllocationStartBlock(),
			"caller allocation period has not started"
		);
		
		uint256 initialBalance = token.balanceOf(this);
		bytes[] memory proofs = new bytes[](_recipients.length);

		uint256 i = 0;
		uint256 j = 0;

		while(i < _merkleProofs.length){
			uint256 proofSize = uint256(BytesUtil.readBytes32(_merkleProofs, i));

			require(
				proofSize % 32 == 0,
				"proof size must be a multiple of 32"
			);

			proofs[j] = BytesUtil.substr(_merkleProofs, i + 32, proofSize);

			i = i + 32 + proofSize;
			j++;
		}

		require(
			_recipients.length == j,
			"number of recipients != number of proofs"
		);

		for (uint256 k = 0; k < _recipients.length; k++) {
			if (!mine.generated(_recipients[k])) {
				mine.generate(_recipients[k], proofs[k]);
			}
		}

		uint256 newBalanceSinceAllocation = token.balanceOf(this);
		uint256 callerTokensGenerated = newBalanceSinceAllocation.sub(initialBalance);

		if (callerTokensGenerated > 0) {
			require(token.transfer(msg.sender, callerTokensGenerated));
		}
	}
}

library BytesUtil{
    uint256 internal constant BYTES_HEADER_SIZE = 32;
    uint256 internal constant WORD_SIZE = 32;

    function dataPtr(bytes memory bts) internal pure returns (uint256 addr) {
        assembly {
            addr := add(bts, 32)
        }
    }

    function copy(uint256 src, uint256 dest, uint256 len) internal pure {
        for (; len >= WORD_SIZE; len -= WORD_SIZE) {
            assembly {
                mstore(dest, mload(src))
            }
            dest += WORD_SIZE;
            src += WORD_SIZE;
        }

        uint256 mask = 256 ** (WORD_SIZE - len) - 1;
        assembly {
            let srcpart := and(mload(src), not(mask))
            let destpart := and(mload(dest), mask)
            mstore(dest, or(destpart, srcpart))
        }
    }

    function toBytes(uint256 addr, uint256 len) internal pure returns (bytes memory bts) {
        bts = new bytes(len);
        uint256 btsptr = dataPtr(bts);
        copy(addr, btsptr, len);
    }
    
    function substr(bytes memory bts, uint256 startIndex, uint256 len) internal pure returns (bytes memory) {
        require(startIndex + len <= bts.length);
        if (len == 0) {
            return;
        }
        uint256 addr = dataPtr(bts);
        return toBytes(addr + startIndex, len);
    }

    function readBytes32(bytes memory bts, uint256 startIndex) internal pure returns (bytes32 result) {
        require(startIndex + 32 <= bts.length);

        uint256 addr = dataPtr(bts);

        assembly {
            result := mload(add(addr, startIndex))
        }

        return result;
    }
}
