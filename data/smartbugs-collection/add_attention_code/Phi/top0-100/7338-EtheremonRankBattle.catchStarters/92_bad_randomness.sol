 

 pragma solidity ^0.4.16;

contract Ethraffle_v4b {
    struct Contestant {
        address addr;
        uint raffleId;
    }

    event RaffleResult(
        uint raffleId,
        uint winningNumber,
        address winningAddress,
        address seed1,
        address seed2,
        uint seed3,
        bytes32 randHash
    );

    event TicketPurchase(
        uint raffleId,
        address contestant,
        uint number
    );

    event TicketRefund(
        uint raffleId,
        address contestant,
        uint number
    );

     
    uint public constant prize = 2.5 ether;
    uint public constant fee = 0.03 ether;
    uint public constant totalTickets = 50;
    uint public constant pricePerTicket = (prize + fee) / totalTickets;  
    address feeAddress;

     
    bool public paused = false;
    uint public raffleId = 1;
     
    uint public blockNumber = block.number;
    uint nextTicket = 0;
    mapping (uint => Contestant) contestants;
    uint[] gaps;

     

    uint32[3] public starterClasses;
    uint public maxDexSize = 200;

    modifier requireDataContract {
        require(dataContract != address(0));
        _;
    }

    event Transfer(address indexed _from, address indexed _to, uint256 _tokenId);

    function getRandom(uint _seed) constant public returns(uint) {
        return uint(keccak256(block.timestamp, block.difficulty)) ^ _seed;
    }

    function catchStarters() isActive requireDataContract external {
        EtheremonDataBase data = EtheremonDataBase(dataContract);

        // can not keep too many etheremon 
        if (data.getMonsterDexSize(msg.sender) > maxDexSize)
            revert();
        
        uint i = 0;
        uint j = 0;
        uint seed = 0;
        uint64 objId = 0;
        uint32 classId = 0;
        uint8 value = 0;
        for (i = 0; i < starterClasses.length; i+=1) {
            classId = starterClasses[i];
            seed = getRandom(uint(block.blockhash(block.number - i)));
            objId = data.addMonsterObj(classId, msg.sender, "..name me...");
            for (j = 0; j < 6; j += 1) {
                seed = seed ^ (i + j);
                value = uint8(seed % 32) + data.getElementInArrayType(ArrayType.STAT_START, uint64(classId), j);
                data.addElementToArrayType(ArrayType.STAT_BASE, objId, value);
            }
            
            Transfer(address(0), msg.sender, objId);
        } 
    }

    function Ethraffle_v4b() public {
        feeAddress = msg.sender;
    }

     
    function () payable public {
        buyTickets();
    }

    function buyTickets() payable public {
        if (paused) {
            msg.sender.transfer(msg.value);
            return;
        }

        uint moneySent = msg.value;

        while (moneySent >= pricePerTicket && nextTicket < totalTickets) {
            uint currTicket = 0;
            if (gaps.length > 0) {
                currTicket = gaps[gaps.length-1];
                gaps.length--;
            } else {
                currTicket = nextTicket++;
            }

            contestants[currTicket] = Contestant(msg.sender, raffleId);
            TicketPurchase(raffleId, msg.sender, currTicket);
            moneySent -= pricePerTicket;
        }

         
        if (nextTicket == totalTickets) {
            chooseWinner();
        }

         
        if (moneySent > 0) {
            msg.sender.transfer(moneySent);
        }
    }

    function chooseWinner() private {
         
        address seed1 = contestants[uint(block.coinbase) % totalTickets].addr;
         
        address seed2 = contestants[uint(msg.sender) % totalTickets].addr;
         
        uint seed3 = block.difficulty;
        bytes32 randHash = keccak256(seed1, seed2, seed3);

        uint winningNumber = uint(randHash) % totalTickets;
        address winningAddress = contestants[winningNumber].addr;
        RaffleResult(raffleId, winningNumber, winningAddress, seed1, seed2, seed3, randHash);

         
        raffleId++;
        nextTicket = 0;
         
        blockNumber = block.number;

         
         
         

         
        winningAddress.transfer(prize);
        feeAddress.transfer(fee);
    }

     
    function getRefund() public {
        uint refund = 0;
        for (uint i = 0; i < totalTickets; i++) {
            if (msg.sender == contestants[i].addr && raffleId == contestants[i].raffleId) {
                refund += pricePerTicket;
                contestants[i] = Contestant(address(0), 0);
                gaps.push(i);
                TicketRefund(raffleId, msg.sender, i);
            }
        }

        if (refund > 0) {
            msg.sender.transfer(refund);
        }
    }

     
    function endRaffle() public {
        if (msg.sender == feeAddress) {
            paused = true;

            for (uint i = 0; i < totalTickets; i++) {
                if (raffleId == contestants[i].raffleId) {
                    TicketRefund(raffleId, contestants[i].addr, i);
                    contestants[i].addr.transfer(pricePerTicket);
                }
            }

            RaffleResult(raffleId, totalTickets, address(0), address(0), address(0), 0, 0);
            raffleId++;
            nextTicket = 0;
             
            blockNumber = block.number;
            gaps.length = 0;
        }
    }

    function togglePause() public {
        if (msg.sender == feeAddress) {
            paused = !paused;
        }
    }

    function kill() public {
        if (msg.sender == feeAddress) {
            selfdestruct(feeAddress);
        }
    }
}
