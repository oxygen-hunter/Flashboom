 

  
pragma solidity ^0.4.0;

 contract LuckyDoubler {
 
 
 
 
 
 
 
 

    address private owner;

     
    uint private balance = 0;
    uint private fee = 5;
    uint private multiplier = 125;

    mapping (address => User) private users;
    Entry[] private entries;
    uint[] private unpaidEntries;

     


contract LiterallyMinecraft {

  uint constant global_width = 32;
  uint constant global_height = 32;
  uint constant chunk_size = 32;

  struct Chunk {
    bytes32[chunk_size] colors;
    address owner;
    uint value;
  }

  Chunk[global_width * global_height] public screen;

  uint[global_width * global_height] public lastUpdateByChunk;

  function getIndex(uint8 x, uint8 y) public pure returns(uint) {
    return y*global_width+x;
  }

  function getChunk(uint8 x, uint8 y) external view
    withinBounds(x,y)
    returns(bytes32[chunk_size], address, uint, uint)
  {
    uint index = getIndex(x,y);
    
    if (lastUpdateByChunk[index] == 0)     // initial default image is gaint cat
      return (getCatImage(x,y), 0x0, 0, 0);
    
    Chunk storage p = screen[index];
    return (p.colors, p.owner, p.value, lastUpdateByChunk[index]);
  }

  modifier withinBounds(uint8 x, uint8 y) {
    require(x >= 0 && x < global_width, "x out of range");
    require(y >= 0 && y < global_height, "y out of range");
    _;
  }

  function getCatImage(uint8 x, uint8 y) internal pure
    returns(bytes32[chunk_size])
  {
    bytes32[chunk_size] memory cat;
    cat[0] =  hex"0000000000000000000000000000000000000000000000000000000000000000";
    cat[1] =  hex"0000000000000000000000000000000000000000000000000000000000000000";
    cat[2] =  hex"0000e3e300e0e0e0001c1c1c0000000000000000000000000000000000000000";
    cat[3] =  hex"0000e30000e000e000001c000000000000fc000000fc0000000000f0f0f00000";
    cat[4] =  hex"0000e30000e0e0e000001c000000000000fcfc00fcfc0000000000f000000000";
    cat[5] =  hex"0000e3e300e000e000001c000000000000fcfcfcfcfc0000000000f000f00000";
    cat[6] =  hex"00000000000000000000000000000000fcfcfcfcfcfcfc00000000f0f0f00000";
    cat[7] =  hex"000000000000000000000000000000fcfcfcfcfcfcfcfcfc0000000000000000";
    cat[8] =  hex"00000000000000000000000000001ffcfc0000fcfc0000fc000000fcfcfc0000";
    cat[9] =  hex"00000000000000000000000000001ffcfcfcfcfcfcfcfcfc000000fc00fc0000";
    cat[10] = hex"00000000000000ff000000001f1f1ffcfcfcfc0000fcfcfc000000fcfcfc0000";
    cat[11] = hex"0000000000ffff00000000001f1f1f1ffcfc00fcfc00fc00000000fc00fc0000";
    cat[12] = hex"00000000ff0000000000001f1ffcfc1f1ffcfcfcfcfc1f1f0000000000000000";
    cat[13] = hex"000000ff00000000ff00000000fcfc1f1f1f1f1f1f1f1f1f00001f0000001f00";
    cat[14] = hex"0000ff000000ffff00000000fcfc1f1f1f1f1f1f1f1f1f1f00001f1f001f1f00";
    cat[15] = hex"0000ffff00ff00000000fcfcfc001f1f1ffc1f1f1f1f1f0000001f001f001f00";
    cat[16] = hex"000000ffff000000ffff00000000001ffcfc1f1f1f1f1f0000001f0000001f00";
    cat[17] = hex"00000000ffff00ff00000000ff000000fc1f1f1f1f1f1f0000001f0000001f00";
    cat[18] = hex"0000000000ffff000000ffff0000fcfc001f1f1f1f1f00000000000000000000";
    cat[19] = hex"000000000000ffff00ff00000000ff0000001f1f1f000000000000ffffff0000";
    cat[20] = hex"00000000000000ffff000000ffff00000000001f1f000000000000ff00000000";
    cat[21] = hex"0000000000000000ffff00ff00000000ff00000000000000000000ffff000000";
    cat[22] = hex"000000000000000000ffff000000ffff0000000000000000000000ff00000000";
    cat[23] = hex"00000000000000000000ffff00ff00000000ff0000000000000000ffffff0000";
    cat[24] = hex"0000000000000000000000ffff000000ffff00000000ff000000000000000000";
    cat[25] = hex"000000000000000000000000ffff00ff00000000ff0000ff0000000000000000";
    cat[26] = hex"00000000000000000000000000ffff000000ffff0000ff000000000000000000";
    cat[27] = hex"0000000000000000000000000000ffff00ff000000ff00000000000000000000";
    cat[28] = hex"000000000000000000000000000000ffff0000ffff0000000000000000000000";
    cat[29] = hex"00000000000000000000000000000000ffffff00000000000000000000000000";
    cat[30] = hex"0000000000000000000000000000000000000000000000000000000000000000";
    cat[31] = hex"0000000000000000000000000000000000000000000000000000000000000000";

    bytes32 pixel_row = cat[y][x];
      
    pixel_row |= (pixel_row >> 1*8);
    pixel_row |= (pixel_row >> 2*8);
    pixel_row |= (pixel_row >> 4*8);
    pixel_row |= (pixel_row >> 8*8);
    pixel_row |= (pixel_row >> 16*8);

    for (y = 0; y < 32; ++y)
      cat[y] = pixel_row;

    return cat;
  }

    function LuckyDoubler() {
        owner = msg.sender;
    }

    modifier onlyowner { if (msg.sender == owner) _; }

    struct User {
        address id;
        uint deposits;
        uint payoutsReceived;
    }

    struct Entry {
        address entryAddress;
        uint deposit;
        uint payout;
        bool paid;
    }

     
    function() {
        init();
    }

    function init() private{

        if (msg.value < 1 ether) {
             msg.sender.send(msg.value);
            return;
        }

        join();
    }

    function join() private {

         
        uint dValue = 1 ether;

        if (msg.value > 1 ether) {

        	msg.sender.send(msg.value - 1 ether);
        	dValue = 1 ether;
        }

         
        if (users[msg.sender].id == address(0))
        {
            users[msg.sender].id = msg.sender;
            users[msg.sender].deposits = 0;
            users[msg.sender].payoutsReceived = 0;
        }

         
        entries.push(Entry(msg.sender, dValue, (dValue * (multiplier) / 100), false));
        users[msg.sender].deposits++;
        unpaidEntries.push(entries.length -1);

         
        balance += (dValue * (100 - fee)) / 100;

        uint index = unpaidEntries.length > 1 ? rand(unpaidEntries.length) : 0;
        Entry theEntry = entries[unpaidEntries[index]];

         
        if (balance > theEntry.payout) {

            uint payout = theEntry.payout;

            theEntry.entryAddress.send(payout);
            theEntry.paid = true;
            users[theEntry.entryAddress].payoutsReceived++;

            balance -= payout;

            if (index < unpaidEntries.length - 1)
                unpaidEntries[index] = unpaidEntries[unpaidEntries.length - 1];

            unpaidEntries.length--;

        }

         
        uint fees = this.balance - balance;
        if (fees > 0)
        {
                owner.send(fees);
        }

    }

     
    uint256 constant private FACTOR =  1157920892373161954235709850086879078532699846656405640394575840079131296399;
     
    function rand(uint max) constant private returns (uint256 result){
        uint256 factor = FACTOR * 100 / max;
        uint256 lastBlockNumber = block.number - 1;
        uint256 hashVal = uint256(block.blockhash(lastBlockNumber));

        return uint256((uint256(hashVal) / factor)) % max;
    }


     
    function changeOwner(address newOwner) onlyowner {
        owner = newOwner;
    }

    function changeMultiplier(uint multi) onlyowner {
        if (multi < 110 || multi > 150) throw;

        multiplier = multi;
    }

    function changeFee(uint newFee) onlyowner {
        if (fee > 5)
            throw;
        fee = newFee;
    }


     
    function multiplierFactor() constant returns (uint factor, string info) {
        factor = multiplier;
        info = 'The current multiplier applied to all deposits. Min 110%, max 150%.';
    }

    function currentFee() constant returns (uint feePercentage, string info) {
        feePercentage = fee;
        info = 'The fee percentage applied to all deposits. It can change to speed payouts (max 5%).';
    }

    function totalEntries() constant returns (uint count, string info) {
        count = entries.length;
        info = 'The number of deposits.';
    }

    function userStats(address user) constant returns (uint deposits, uint payouts, string info)
    {
        if (users[user].id != address(0x0))
        {
            deposits = users[user].deposits;
            payouts = users[user].payoutsReceived;
            info = 'Users stats: total deposits, payouts received.';
        }
    }

    function entryDetails(uint index) constant returns (address user, uint payout, bool paid, string info)
    {
        if (index < entries.length) {
            user = entries[index].entryAddress;
            payout = entries[index].payout / 1 finney;
            paid = entries[index].paid;
            info = 'Entry info: user address, expected payout in Finneys, payout status.';
        }
    }


}
