 

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
