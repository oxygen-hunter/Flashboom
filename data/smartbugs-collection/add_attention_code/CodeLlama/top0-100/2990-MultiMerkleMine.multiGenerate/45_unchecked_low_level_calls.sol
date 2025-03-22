 

pragma solidity ^0.4.11;  

contract Owned {
    function Owned() {
        owner = msg.sender;
    }

    address public owner;

     
     
     
    modifier onlyOwner { if (msg.sender == owner) _; }

    function changeOwner(address _newOwner) onlyOwner {
        owner = _newOwner;
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
         
        _dst.call.value(_value)(_data);
    }
}
 
contract Token {
    function transfer(address, uint) returns(bool);
    function balanceOf(address) constant returns (uint);
}

contract TokenSender is Owned {
    Token public token;  
    uint public totalToDistribute;

    uint public next;


    struct Transfer {
        address addr;
        uint amount;
    }

    Transfer[] public transfers;

    function TokenSender(address _token) {
        token = Token(_token);
    }

     
    uint constant D160 = 0x0010000000000000000000000000000000000000000;

     
     
     
     
     
     
    function fill(uint[] data) onlyOwner {

         
        if (next>0) throw;

        uint acc;
        uint offset = transfers.length;
        transfers.length = transfers.length + data.length;
        for (uint i = 0; i < data.length; i++ ) {
            address addr = address( data[i] & (D160-1) );
            uint amount = data[i] / D160;

            transfers[offset + i].addr = addr;
            transfers[offset + i].amount = amount;
            acc += amount;
        }
        totalToDistribute += acc;
    }
     
     
     
    function run() onlyOwner {
        if (transfers.length == 0) return;

         
        uint mNext = next;

         
        next = transfers.length;

        if ((mNext == 0 ) && ( token.balanceOf(this) != totalToDistribute)) throw;

        while ((mNext<transfers.length) && ( gas() > 150000 )) {
            uint amount = transfers[mNext].amount;
            address addr = transfers[mNext].addr;
            if (amount > 0) {
                if (!token.transfer(addr, transfers[mNext].amount)) throw;
            }
            mNext ++;
        }

         
        next = mNext;
    }


     
     
     

    function hasTerminated() constant returns (bool) {
        if (transfers.length == 0) return false;
        if (next < transfers.length) return false;
        return true;
    }

    function nTransfers() constant returns (uint) {
        return transfers.length;
    }

    function gas() internal constant returns (uint _gas) {
        assembly {
            _gas:= gas
        }
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
