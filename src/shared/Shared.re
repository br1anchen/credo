module Types = {
  type songEntity('lyrics) = {
    id: int,
    name: string,
    lang: string,
    lyrics: 'lyrics,
  }

  type song = songEntity(array(string));
  type songDB = songEntity(list(string));

  type schedule = array(song);
  type scheduleDB = list(songDB);
};